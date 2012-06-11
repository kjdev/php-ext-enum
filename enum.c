
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"

#include "php_enum.h"

static HashTable *enums;

ZEND_BEGIN_ARG_INFO_EX(arginfo_enum, 0, 0, 2)
    ZEND_ARG_INFO(0, class)
    ZEND_ARG_INFO(0, constants)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_enum_vars, 0, 0, 1)
    ZEND_ARG_INFO(0, class)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_enum_exists, 0, 0, 1)
    ZEND_ARG_INFO(0, name)
ZEND_END_ARG_INFO()

ZEND_FUNCTION(enum);
ZEND_FUNCTION(enum_vars);
ZEND_FUNCTION(enum_exists);

#if ZEND_MODULE_API_NO >= 20090626
const zend_function_entry enum_functions[] = {
#else
zend_function_entry enum_functions[] = {
#endif
    ZEND_FE(enum, arginfo_enum)
    ZEND_FE(enum_vars, arginfo_enum_vars)
    ZEND_FE(enum_exists, arginfo_enum_exists)
    { NULL, NULL, NULL, 0, 0 }
};

static inline zend_class_entry *_enum_init(char *class, int class_len TSRMLS_DC)
{
    zend_class_entry *ce;
    char *lowercase_name;

    /* Check class defined */
    lowercase_name = emalloc(class_len+1);
    zend_str_tolower_copy(lowercase_name, class, class_len);
#if ZEND_MODULE_API_NO >= 20100525
    lowercase_name = (char *)zend_new_interned_string(lowercase_name,
                                                      class_len+1,
                                                      1 TSRMLS_CC);
#endif

    if (zend_hash_exists(CG(class_table), lowercase_name, class_len+1)) {
#if ZEND_MODULE_API_NO >= 20100525
        str_efree(lowercase_name);
#else
        efree(lowercase_name);
#endif
        return NULL;
    }

    /* Init class interface */
    ce = (zend_class_entry *)emalloc(sizeof(zend_class_entry));

#if ZEND_MODULE_API_NO >= 20090626
    INIT_CLASS_ENTRY_EX((*ce), class, class_len, NULL);
#else
    ce->name = strdup(class);
    ce->name_length = class_len;
    ce->builtin_functions = NULL;
    ce->constructor = NULL;
    ce->destructor = NULL;
    ce->clone = NULL;
    ce->serialize = NULL;
    ce->unserialize = NULL;
    ce->create_object = NULL;
    ce->interface_gets_implemented = NULL;
    ce->__call = NULL;
    ce->__tostring = NULL;
    ce->__get = NULL;
    ce->__set = NULL;
    ce->__unset = NULL;
    ce->__isset = NULL;
    ce->serialize_func = NULL;
    ce->unserialize_func = NULL;
    ce->serialize = NULL;
    ce->unserialize = NULL;
    ce->parent = NULL;
    ce->num_interfaces = 0;
    ce->interfaces = NULL;
    ce->get_iterator = NULL;
    ce->iterator_funcs.funcs = NULL;
    ce->module = NULL;
#endif

    ce->type = ZEND_INTERNAL_CLASS;
    zend_initialize_class_data(ce, 0 TSRMLS_CC);
    ce->ce_flags =  ZEND_ACC_INTERFACE;
#if ZEND_MODULE_API_NO >= 20100525
    ce->info.internal.module = EG(current_module);
    /*
    if (ce->info.internal.builtin_functions) {
        zend_register_functions(ce, ce->info.internal.builtin_functions,
                                &ce->function_table,
                                MODULE_PERSISTENT TSRMLS_CC);
    }
    */
    if (IS_INTERNED(lowercase_name)) {
        zend_hash_quick_update(CG(class_table), lowercase_name,
                               ce->name_length+1, INTERNED_HASH(lowercase_name),
                               &ce, sizeof(zend_class_entry *), NULL);
    } else {
        zend_hash_update(CG(class_table), lowercase_name, ce->name_length+1,
                         &ce, sizeof(zend_class_entry *), NULL);
    }
#else
    ce->module = EG(current_module);
    /*
    if (ce->builtin_functions) {
        zend_register_functions(ce, ce->builtin_functions, &ce->function_table,
                                MODULE_PERSISTENT TSRMLS_CC);
    }
    */
    ce->refcount++;
    zend_hash_update(CG(class_table), lowercase_name, ce->name_length+1,
                     &ce, sizeof(zend_class_entry *), NULL);
#endif


#if ZEND_MODULE_API_NO >= 20100525
    str_efree(lowercase_name);
#else
    efree(lowercase_name);
#endif

    zend_hash_add(enums, class, class_len,
                  (void *)&ce, sizeof(zend_class_entry*), NULL);

    return ce;
}

static inline void _enum_destroy(zend_class_entry **data)
{
    if (*data) {
#if ZEND_MODULE_API_NO < 20100525
        TSRMLS_FETCH();
        char *lowercase_name;
        lowercase_name = emalloc((*data)->name_length+2);
        zend_str_tolower_copy(lowercase_name,
                              (*data)->name, (*data)->name_length+1);
        zend_hash_del(CG(class_table), lowercase_name, (*data)->name_length+1);
        efree(lowercase_name);
#endif
        efree(*data);
    }
}

ZEND_MINIT_FUNCTION(enum)
{
    return SUCCESS;
}

ZEND_MSHUTDOWN_FUNCTION(enum)
{
    return SUCCESS;
}

ZEND_RINIT_FUNCTION(enum)
{
    ALLOC_HASHTABLE(enums);
    zend_hash_init(enums, 10, NULL, (void (*)(void *))_enum_destroy, 0);
    return SUCCESS;
}

ZEND_RSHUTDOWN_FUNCTION(enum)
{
    if (enums) {
        zend_hash_destroy(enums);
        FREE_HASHTABLE(enums);
    }
    return SUCCESS;
}

ZEND_MINFO_FUNCTION(enum)
{
    php_info_print_table_start();
    php_info_print_table_header(2, "enum support", "enabled");
    php_info_print_table_header(2, "extension version", ENUM_EXT_VERSION);
    php_info_print_table_end();
}

zend_module_entry enum_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
    STANDARD_MODULE_HEADER,
#endif
    "enum",
    enum_functions,
    ZEND_MINIT(enum),
    ZEND_MSHUTDOWN(enum),
    ZEND_RINIT(enum),
    ZEND_RSHUTDOWN(enum),
    ZEND_MINFO(enum),
#if ZEND_MODULE_API_NO >= 20010901
    ENUM_EXT_VERSION,
#endif
    STANDARD_MODULE_PROPERTIES
};

#ifdef COMPILE_DL_ENUM
ZEND_GET_MODULE(enum)
#endif

ZEND_FUNCTION(enum)
{
    char *class;
    int class_len;
    zval *constants;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
                              "sz", &class, &class_len, &constants) == FAILURE) {
        RETURN_FALSE;
    }

    if (!class || class_len <= 0) {
        zend_error(E_ERROR, "Cannot empty class name");
        RETURN_FALSE;
    }

    if (!constants ||
        (Z_TYPE_P(constants) != IS_STRING &&
         Z_TYPE_P(constants) != IS_ARRAY &&
         Z_TYPE_P(constants) != IS_OBJECT)) {
        zend_error(E_ERROR, "Invalid type constants");
        RETURN_FALSE;
    }

    /* Create class interface */
    zend_class_entry *ce = _enum_init(class, class_len TSRMLS_CC);
    if (!ce) {
        zend_error(E_ERROR, "Cannot redeclare class '%s'", class);
        RETURN_FALSE;
    }

    /* Interface constant */
    if (Z_TYPE_P(constants) == IS_STRING) {
        if (Z_STRLEN_P(constants) <= 0) {
            zend_error(E_WARNING, "Cannot empty constant name");
            RETURN_TRUE;
        }
        zend_declare_class_constant_long(ce, Z_STRVAL_P(constants),
                                         Z_STRLEN_P(constants), 0 TSRMLS_CC);
    } else {
        ulong constant_num = 0;
        char *key;
        zval **data;
        ulong key_index;
        HashPosition pos;
        int key_type;

        HashTable *ht = HASH_OF(constants);

        if (zend_hash_num_elements(ht) <= 0) {
            zend_error(E_WARNING, "Cannot empty data constants");
            RETURN_TRUE;
        }

        zend_hash_internal_pointer_reset_ex(ht, &pos);

        for (;; zend_hash_move_forward_ex(ht, &pos)) {
            key_type = zend_hash_get_current_key_ex(ht, &key, NULL,
                                             &key_index, 0, &pos);
            if (key_type == HASH_KEY_NON_EXISTANT) {
                break;
            }

            if (zend_hash_get_current_data_ex(ht, (void **)&data,
                                              &pos) != SUCCESS) {
                zend_error(E_WARNING, "Invalid data constants");
                continue;
            }
            if (key_type == HASH_KEY_IS_LONG &&
                Z_TYPE_PP(data) == IS_STRING) {
                if (zend_hash_exists(&(ce->constants_table),
                                     Z_STRVAL_PP(data), Z_STRLEN_PP(data)+1)) {
                    zend_error(E_WARNING, "Redeclare enum constant '%s::%s'",
                               class, Z_STRVAL_PP(data));
                }
                zend_declare_class_constant_long(
                    ce, Z_STRVAL_PP(data), Z_STRLEN_PP(data),
                    constant_num++ TSRMLS_CC);
            } else if (key_type == HASH_KEY_IS_STRING) {
                if (zend_hash_exists(&(ce->constants_table),
                                     key, strlen(key)+1)) {
                    zend_error(E_WARNING, "Redeclare enum constant '%s::%s'",
                               class, key);
                }
                switch (Z_TYPE_PP(data)) {
                    case IS_LONG:
                        constant_num = Z_LVAL_PP(data);
                        zend_declare_class_constant_long(
                            ce, key, strlen(key), constant_num++ TSRMLS_CC);
                        break;
                    case IS_NULL:
                        zend_declare_class_constant_null(
                            ce, key, strlen(key) TSRMLS_CC);
                        break;
                    case IS_BOOL:
                        zend_declare_class_constant_bool(
                            ce, key, strlen(key), Z_BVAL_PP(data) TSRMLS_CC);
                        break;
                    case IS_DOUBLE:
                        zend_declare_class_constant_double(
                            ce, key, strlen(key), Z_DVAL_PP(data) TSRMLS_CC);
                        break;
                    case IS_STRING:
                        zend_declare_class_constant_stringl(
                            ce, key, strlen(key), Z_STRVAL_PP(data),
                            Z_STRLEN_PP(data) TSRMLS_CC);
                        break;
                    default:
                        zend_error(E_WARNING, "Invalid data constants");
                        break;
                }
            } else {
                zend_error(E_WARNING, "Invalid data constants");
            }
        }
    }

    RETURN_TRUE;
}

ZEND_FUNCTION(enum_vars)
{
    zval *class, *tmp_copy;
    zend_class_entry *ce = NULL, **pce;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
                              "z", &class) == FAILURE) {
        RETURN_FALSE;
    }

    if (Z_TYPE_P(class) == IS_OBJECT) {
        if (Z_OBJ_HT_P(class)->get_class_entry != NULL) {
            ce = Z_OBJCE_P(class);
        }
    } else if (Z_TYPE_P(class) == IS_STRING) {
        if (zend_lookup_class(Z_STRVAL_P(class), Z_STRLEN_P(class),
                              &pce TSRMLS_CC) == SUCCESS) {
            ce = *pce;
        }
    }

    if (!ce) {
        zend_error(E_WARNING, "Does not exists class");
        RETURN_FALSE;
    }

    array_init(return_value);

#if PHP_VERSION_ID >= 50303
    zend_hash_apply_with_argument(
        &ce->constants_table,
        (apply_func_arg_t)zval_update_constant_inline_change, ce TSRMLS_CC);
#else
    zend_hash_apply_with_argument(&ce->constants_table,
                                  (apply_func_arg_t)zval_update_constant,
                                  (void*)1 TSRMLS_CC);
#endif

    zend_hash_copy(Z_ARRVAL_P(return_value), &ce->constants_table,
                   (copy_ctor_func_t)zval_add_ref, (void *)&tmp_copy,
                   sizeof(zval*));
}

ZEND_FUNCTION(enum_exists)
{
    char *name;
    int name_len;
    zval zv;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s",
                              &name, &name_len) == FAILURE) {
        RETURN_FALSE;
    }

#if ZEND_MODULE_API_NO >= 20090626
    if (zend_get_constant_ex(name, name_len, &zv, NULL,
                             ZEND_FETCH_CLASS_SILENT TSRMLS_CC)) {
        zval_dtor(&zv);
        RETURN_TRUE;
    } else {
        RETURN_FALSE;
    }
#else
    if (zend_get_constant(name, name_len, &zv TSRMLS_CC)) {
        zval_dtor(&zv);
        RETURN_TRUE;
    } else {
        RETURN_FALSE;
    }
#endif
}
