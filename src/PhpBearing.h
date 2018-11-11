//
// Created by Jack Noordhuis on 2/11/18.
//

#ifndef EXT_POCKETMINE_MATH_PHPBEARING_H
#define EXT_POCKETMINE_MATH_PHPBEARING_H

#include "ZendUtil.h"

// Defines so we can use our macros in ZendUtil.h.
#define CLASS_TYPE Bearing

PHP_CLASS_METHOD(toFacing);
PHP_CLASS_METHOD(fromFacing);
PHP_CLASS_METHOD(fromAngle);
PHP_CLASS_METHOD(rotate);
PHP_CLASS_METHOD(opposite);

void register_bearing_class();

// Undefine so we can use the macros for other classes.
#undef CLASS_TYPE

#endif //EXT_POCKETMINE_MATH_PHPBEARING_H
