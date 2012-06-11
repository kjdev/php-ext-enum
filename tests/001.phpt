--TEST--
Check functions
--FILE--
<?php
if (!extension_loaded('enum')) {
    dl('enum.' . PHP_SHLIB_SUFFIX);
}

var_dump(function_exists('enum'));
var_dump(function_exists('enum_vars'));
var_dump(function_exists('enum_exists'));
?>
--EXPECT--
bool(true)
bool(true)
bool(true)
