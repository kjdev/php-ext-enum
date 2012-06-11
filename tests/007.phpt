--TEST--
Check type hinting
--FILE--
<?php
if (!extension_loaded('enum')) {
    dl('enum.' . PHP_SHLIB_SUFFIX);
}

var_dump(enum('Test', array('a', 'b', 'c')));
var_dump(enum_vars('Test'));

class a implements Test {}
var_dump(enum_vars('a'));

$a = new a;

function type_a(a $obj = NULL) {}
function type_Test(Test $obj = NULL) {}

var_dump($a instanceof a);
var_dump($a instanceof Test);

type_a($a);
type_Test($a);
?>
==DONE==
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
bool(true)
bool(true)
==DONE==
