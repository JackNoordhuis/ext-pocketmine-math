//
// Created by Jack Noordhuis on 1/11/18.
//

#ifndef EXT_POCKETMINE_MATH_PHPFACING_H
#define EXT_POCKETMINE_MATH_PHPFACING_H

#include "ZendUtil.h"

// Defines so we can use our macros in ZendUtil.h.
#define CLASS_TYPE Facing

PHP_CLASS_METHOD(axis);
PHP_CLASS_METHOD(isPositive);
PHP_CLASS_METHOD(opposite);
PHP_CLASS_METHOD(rotate);
PHP_CLASS_METHOD(validate);

void register_facing_class();

// Undefine so we can use the macros for other classes.
#undef CLASS_TYPE

#endif //EXT_POCKETMINE_MATH_PHPFACING_H
