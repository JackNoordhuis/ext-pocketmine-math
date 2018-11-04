//
// Created by Jack Noordhuis on 2/11/18.
//

#ifndef EXT_POCKETMINE_MATH_PHPVECTOR2_H
#define EXT_POCKETMINE_MATH_PHPVECTOR2_H

extern "C" {
#include "php.h"
}

class Vector2;

PHP_METHOD(PhpVector2, __construct);
PHP_METHOD(PhpVector2, getX);
PHP_METHOD(PhpVector2, getY);
PHP_METHOD(PhpVector2, getFloorX);
PHP_METHOD(PhpVector2, getFloorY);
PHP_METHOD(PhpVector2, add);
PHP_METHOD(PhpVector2, subtract);
PHP_METHOD(PhpVector2, ceil);
PHP_METHOD(PhpVector2, floor);
PHP_METHOD(PhpVector2, round);
PHP_METHOD(PhpVector2, abs);
PHP_METHOD(PhpVector2, multiply);
PHP_METHOD(PhpVector2, divide);
PHP_METHOD(PhpVector2, distance);
PHP_METHOD(PhpVector2, distanceSquared);
PHP_METHOD(PhpVector2, length);
PHP_METHOD(PhpVector2, lengthSquared);
PHP_METHOD(PhpVector2, normalize);
PHP_METHOD(PhpVector2, dot);
PHP_METHOD(PhpVector2, __toString);

void register_vector2_class();

typedef struct {
    Vector2 *container;
    zend_object std;
} Vector2_obj;

#endif //EXT_POCKETMINE_MATH_PHPVECTOR2_H
