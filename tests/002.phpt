--TEST--
Check create
--FILE--
<?php
if (!extension_loaded('enum')) {
    dl('enum.' . PHP_SHLIB_SUFFIX);
}

function create_test($name, $val) {
    echo "--$name--\n";
    $retval = enum($name, $val);
    var_dump($retval);
}

create_test('Test_String', 'a');
var_dump(Test_String::a);
var_dump(enum_vars('Test_String'));

create_test('Test_Array', array('a', 'b', 'c'));
var_dump(Test_Array::a);
var_dump(Test_Array::b);
var_dump(Test_Array::c);
var_dump(enum_vars('Test_Array'));

create_test('Test_Map', array('a' => 1, 'b' => 3, 'c' => 5));
var_dump(Test_Map::a);
var_dump(Test_Map::b);
var_dump(Test_Map::c);
var_dump(enum_vars('Test_Map'));

create_test('Test_Map_Mix', array('a' => 'string',
                                  'b' => null,
                                  'c' => true,
                                  'd' => false,
                                  'e' => 12.345));
var_dump(Test_Map_Mix::a);
var_dump(Test_Map_Mix::b);
var_dump(Test_Map_Mix::c);
var_dump(Test_Map_Mix::d);
var_dump(Test_Map_Mix::e);
var_dump(enum_vars('Test_Map_Mix'));

create_test('Test_Mix', array('a', 'b', 'c' => 10, 'd',
                              'e' => 'string', 'f', 'g' => -10, 'h'));
var_dump(Test_Mix::a);
var_dump(Test_Mix::b);
var_dump(Test_Mix::c);
var_dump(Test_Mix::d);
var_dump(Test_Mix::e);
var_dump(Test_Mix::f);
var_dump(Test_Mix::g);
var_dump(Test_Mix::h);
var_dump(enum_vars('Test_Mix'));
?>
--EXPECT--
--Test_String--
bool(true)
int(0)
array(1) {
  ["a"]=>
  int(0)
}
--Test_Array--
bool(true)
int(0)
int(1)
int(2)
array(3) {
  ["a"]=>
  int(0)
  ["b"]=>
  int(1)
  ["c"]=>
  int(2)
}
--Test_Map--
bool(true)
int(1)
int(3)
int(5)
array(3) {
  ["a"]=>
  int(1)
  ["b"]=>
  int(3)
  ["c"]=>
  int(5)
}
--Test_Map_Mix--
bool(true)
string(6) "string"
NULL
bool(true)
bool(false)
float(12.345)
array(5) {
  ["a"]=>
  string(6) "string"
  ["b"]=>
  NULL
  ["c"]=>
  bool(true)
  ["d"]=>
  bool(false)
  ["e"]=>
  float(12.345)
}
--Test_Mix--
bool(true)
int(0)
int(1)
int(10)
int(11)
string(6) "string"
int(12)
int(-10)
int(-9)
array(8) {
  ["a"]=>
  int(0)
  ["b"]=>
  int(1)
  ["c"]=>
  int(10)
  ["d"]=>
  int(11)
  ["e"]=>
  string(6) "string"
  ["f"]=>
  int(12)
  ["g"]=>
  int(-10)
  ["h"]=>
  int(-9)
}
