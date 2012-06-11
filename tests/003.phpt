--TEST--
Check redeclare
--FILE--
<?php
if (!extension_loaded('enum')) {
    dl('enum.' . PHP_SHLIB_SUFFIX);
}

$retval = enum('Test', array('a', 'b', 'c'));
var_dump($retval);

$retval = enum('Test', array('A', 'B', 'C'));
var_dump($retval);

var_dump(enum_vars('Test'));
?>
--EXPECTF--
bool(true)

Fatal error: Cannot redeclare class 'Test' in %s003.php on line %d
