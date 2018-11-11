//
// Created by Jack Noordhuis on 12/11/18.
//

#ifndef EXT_POCKETMINE_MATH_PHPVECTOR3_H
#define EXT_POCKETMINE_MATH_PHPVECTOR3_H

#include "ZendUtil.h"

class Vector3;

// Defines so we can use our macros in ZendUtil.h.
#define CLASS_TYPE Vector3

PHP_CLASS_METHOD(__construct);
PHP_CLASS_METHOD(__toString);

void register_vector3_class();

zend_class_entry *vector3_class_entry();

// Undefine so we can use the macros for other classes.
#undef CLASS_TYPE

#endif //EXT_POCKETMINE_MATH_PHPVECTOR3_H
