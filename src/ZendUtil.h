//
// Created by Jack Noordhuis on 1/11/18.
//

#ifndef EXT_POCKETMINE_MATH_ZENDUTIL_H
#define EXT_POCKETMINE_MATH_ZENDUTIL_H

extern "C" {
#include "php.h"
}

template<typename class_name>
static inline class_name * fetch_from_zend_object(zend_object *obj) {
    return (class_name *)((char *)obj - XtOffsetOf(class_name, std));
}

#endif //EXT_POCKETMINE_MATH_ZENDUTIL_H
