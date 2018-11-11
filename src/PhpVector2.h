//
// Created by Jack Noordhuis on 2/11/18.
//

#ifndef EXT_POCKETMINE_MATH_PHPVECTOR2_H
#define EXT_POCKETMINE_MATH_PHPVECTOR2_H

#include "ZendUtil.h"

class Vector2;

// Defines so we can use our macros in ZendUtil.h.
#define CLASS_TYPE Vector2

PHP_CLASS_METHOD(__construct);
PHP_CLASS_METHOD(getX);
PHP_CLASS_METHOD(getY);
PHP_CLASS_METHOD(getFloorX);
PHP_CLASS_METHOD(getFloorY);
PHP_CLASS_METHOD(add);
PHP_CLASS_METHOD(subtract);
PHP_CLASS_METHOD(ceil);
PHP_CLASS_METHOD(floor);
PHP_CLASS_METHOD(round);
PHP_CLASS_METHOD(abs);
PHP_CLASS_METHOD(multiply);
PHP_CLASS_METHOD(divide);
PHP_CLASS_METHOD(distance);
PHP_CLASS_METHOD(distanceSquared);
PHP_CLASS_METHOD(length);
PHP_CLASS_METHOD(lengthSquared);
PHP_CLASS_METHOD(normalize);
PHP_CLASS_METHOD(dot);
PHP_CLASS_METHOD(__toString);

void register_vector2_class();

// Undefine so we can use the macros for other classes.
#undef CLASS_TYPE

#endif //EXT_POCKETMINE_MATH_PHPVECTOR2_H
