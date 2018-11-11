//
// Created by Jack Noordhuis on 6/11/18.
//

#ifndef EXT_POCKETMINE_MATH_PHPMATH_H
#define EXT_POCKETMINE_MATH_PHPMATH_H

#include "ZendUtil.h"

// Defines so we can use our macros in ZendUtil.h.
#define CLASS_TYPE Math

PHP_CLASS_METHOD(floorFloat);
PHP_CLASS_METHOD(ceilFloat);
PHP_CLASS_METHOD(solveQuadratic);

void register_math_class();

// Undefine so we can use the macros for other classes.
#undef CLASS_TYPE

#endif //EXT_POCKETMINE_MATH_PHPMATH_H
