--TEST--
Check empty
--FILE--
<?php
if (!extension_loaded('enum')) {
    dl('enum.' . PHP_SHLIB_SUFFIX);
}

var_dump(enum('Test1', array()));
var_dump(enum_vars('Test1'));

var_dump(enum('Test2', ''));
var_dump(enum_vars('Test2'));
?>
--EXPECTF--
Warning: Cannot empty data constants in %s005.php on line %d
bool(true)
array(0) {
}

Warning: Cannot empty constant name in %s005.php on line %d
bool(true)
array(0) {
}
