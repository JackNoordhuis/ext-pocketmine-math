//
// Created by Jack Noordhuis on 11/11/18.
//

#ifndef EXT_POCKETMINE_MATH_PHPRAYTRACERESULT_H
#define EXT_POCKETMINE_MATH_PHPRAYTRACERESULT_H

#include "ZendUtil.h"

class RayTraceResult;

// Defines so we can use our macros in ZendUtil.h.
#define CLASS_TYPE RayTraceResult

PHP_CLASS_METHOD(__construct);
PHP_CLASS_METHOD(getBoundingBox);
PHP_CLASS_METHOD(getHitFace);
PHP_CLASS_METHOD(getHitVector);

void register_raytraceresult_class();

zend_class_entry *raytraceresult_class_entry();

// Undefine so we can use the macros for other classes.
#undef CLASS_TYPE

#endif //EXT_POCKETMINE_MATH_PHPRAYTRACERESULT_H
