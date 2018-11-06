//
// Created by Jack Noordhuis on 6/11/18.
//

#ifndef EXT_POCKETMINE_MATH_PHPMATH_H
#define EXT_POCKETMINE_MATH_PHPMATH_H

extern "C" {
#include "php.h"
}

PHP_METHOD(PhpMath, floorFloat);
PHP_METHOD(PhpMath, ceilFloat);
PHP_METHOD(PhpMath, solveQuadratic);

void register_math_class();

#endif //EXT_POCKETMINE_MATH_PHPMATH_H
