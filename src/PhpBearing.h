//
// Created by Jack Noordhuis on 2/11/18.
//

#ifndef EXT_POCKETMINE_MATH_PHPBEARING_H
#define EXT_POCKETMINE_MATH_PHPBEARING_H

extern "C" {
#include "php.h"
}

PHP_METHOD(PhpBearing, toFacing);
PHP_METHOD(PhpBearing, fromFacing);
PHP_METHOD(PhpBearing, fromAngle);
PHP_METHOD(PhpBearing, rotate);
PHP_METHOD(PhpBearing, opposite);

void register_bearing_class();

#endif //EXT_POCKETMINE_MATH_PHPBEARING_H
