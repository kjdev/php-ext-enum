--TEST--
Check redeclare class
--FILE--
<?php
if (!extension_loaded('enum')) {
    dl('enum.' . PHP_SHLIB_SUFFIX);
}

class Test {}

var_dump(enum('Test', array('a', 'b', 'c')));
var_dump(enum_vars('Test'));
?>
==DONE==
--EXPECTF--
Fatal error: Cannot redeclare class 'Test' in %s010.php on line %d
