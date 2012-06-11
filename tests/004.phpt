--TEST--
Check redeclare constants key
--FILE--
<?php
if (!extension_loaded('enum')) {
    dl('enum.' . PHP_SHLIB_SUFFIX);
}

var_dump(enum('Test', array('a', 'a', 'a')));
var_dump(enum_vars('Test'));
?>
--EXPECTF--
Warning: Redeclare enum constant 'Test::a' in %s004.php on line %d

Warning: Redeclare enum constant 'Test::a' in %s004.php on line %d
bool(true)
array(1) {
  ["a"]=>
  int(2)
}
