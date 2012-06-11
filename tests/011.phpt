--TEST--
Check module info
--FILE--
<?php
if (!extension_loaded('enum')) {
    dl('enum.' . PHP_SHLIB_SUFFIX);
}

ob_start();
phpinfo(INFO_MODULES);
$str = ob_get_clean();

$array = explode("\n", $str);

$section = false;
$blank = 0;
foreach ($array as $key => $val) {
    if (strcmp($val, 'enum') == 0 || $section) {
        $section = true;
    } else {
        continue;
    }

    if (empty($val)) {
        $blank++;
        if ($blank == 2) {
            $section = false;
        }
    }

    echo $val, PHP_EOL;
}
?>
--EXPECTF--
enum

enum support => enabled
extension version => 0.0.1
