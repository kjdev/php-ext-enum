# php-ext-enum #

This PHP extension is enum interface.

## Build ##

    % phpize
    % ./configure
    % make
    % make install

## Configration ##

enum.ini:

    extension=enum.so

## Function : enum ##

bool enum( string $name, mixed $constants )

### parameters ###

name:

    The interface name

constants:

    The constant objects

### return values ###

Returns TRUE if the interface succeeded in creating, FALSE otherwise.

## Function : enum_vars ##

bool enum_vars( mixed $interface )

### parameters ###

name:

    An object instance or interface name

### return values ###

An array of constants. Constant name in key, constant value in value.

## Function : enum_exists ##

bool enum_exists( string $name )

### parameters ###

name:

    The constant name

### return values ###

Returns TRUE if the named constant given by name has been defined,
FALSE otherwise.

## Example ##

    enum('Test', array('a', 'b', 'c'));

    echo Test::a;

    enum_vars('Test');

    enum_exists('Test::b');

    class Hoge inplements Test {};
