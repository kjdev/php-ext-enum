--TEST--
Check empty class
--FILE--
<?php
if (!extension_loaded('enum')) {
    dl('enum.' . PHP_SHLIB_SUFFIX);
}

var_dump(enum('', array('a', 'b', 'c')));
?>
==DONE==
--EXPECTF--
Fatal error: Cannot empty class name in %s008.php on line %d