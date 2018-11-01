//
// Created by Jack Noordhuis on 1/11/18.
//

#ifndef EXT_POCKETMINE_MATH_PHPFACING_H
#define EXT_POCKETMINE_MATH_PHPFACING_H

extern "C" {
#include "php.h"
}

PHP_METHOD(PhpFacing, axis);
PHP_METHOD(PhpFacing, isPositive);
PHP_METHOD(PhpFacing, opposite);
PHP_METHOD(PhpFacing, rotate);
PHP_METHOD(PhpFacing, validate);

void register_facing_class();

#endif //EXT_POCKETMINE_MATH_PHPFACING_H
