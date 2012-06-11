--TEST--
Check enum_exists
--FILE--
<?php
if (!extension_loaded('enum')) {
    dl('enum.' . PHP_SHLIB_SUFFIX);
}

var_dump(enum('Test', array('a', 'b', 'c')));

var_dump(enum_exists('Test::a'));
var_dump(enum_exists('Test::d'));
?>
--EXPECTF--
bool(true)
bool(true)
bool(false)
