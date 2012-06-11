--TEST--
Check implements
--FILE--
<?php
if (!extension_loaded('enum')) {
    dl('enum.' . PHP_SHLIB_SUFFIX);
}

var_dump(enum('Test', array('a', 'b', 'c')));
var_dump(enum_vars('Test'));

class a implements Test {}
var_dump(enum_vars('a'));

class b implements Test {}
var_dump(enum_vars(new b));
?>
--EXPECTF--
bool(true)
array(3) {
  ["a"]=>
  int(0)
  ["b"]=>
  int(1)
  ["c"]=>
  int(2)
}
array(3) {
  ["a"]=>
  int(0)
  ["b"]=>
  int(1)
  ["c"]=>
  int(2)
}
array(3) {
  ["a"]=>
  int(0)
  ["b"]=>
  int(1)
  ["c"]=>
  int(2)
}
