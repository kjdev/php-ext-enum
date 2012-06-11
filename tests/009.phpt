--TEST--
Check invalid constants
--FILE--
<?php
if (!extension_loaded('enum')) {
    dl('enum.' . PHP_SHLIB_SUFFIX);
}

var_dump(enum('Test', null));
?>
==DONE==
--EXPECTF--
Fatal error: Invalid type constants in %s009.php on line %d
