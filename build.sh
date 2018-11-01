#!/usr/bin/env bash

#
# This is a personalised build script, it will not work on your system without
# the correct configuration and is only used to streamline development.
#

phpize && ./configure && make install
make clean && phpize --clean
rm -f stubs/pocketmine_math.php && extension-stub pocketmine_math >> stubs/pocketmine_math.php