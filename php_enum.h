#ifndef PHP_ENUM_H
#define PHP_ENUM_H

#define ENUM_EXT_VERSION "0.0.1"

extern zend_module_entry enum_module_entry;
#define phpext_enum_module_ptr &enum_module_entry

#ifdef PHP_WIN32
#   define PHP_ENUM_MODULE_API __declspec(dllexport)
#elif defined(__GNUC__) && __GNUC__ >= 4
#   define PHP_ENUM_MODULE_API __attribute__ ((visibility("default")))
#else
#   define PHP_ENUM_MODULE_API
#endif

#ifdef ZTS
#include "TSRM.h"
#endif

#endif  /* PHP_ENUM_H */
