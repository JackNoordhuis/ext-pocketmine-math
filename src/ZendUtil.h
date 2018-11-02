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

#define REGISTER_CLASS_CONST_LONG(class_entry, name, value) \
	zend_declare_class_constant_long(class_entry, name, sizeof(name)-1, (zend_long)value)

#define REGISTER_CLASS_CONST_LONG_ARRAY(class_entry, name, value) do { \
    HashTable *ht; \
    ALLOC_HASHTABLE(ht); \
    int value_len = sizeof(value)/sizeof(value[0]); \
    zend_hash_init(ht, value_len, NULL, NULL, 0); \
        for(int i = 0; i < value_len; ++i) { \
        zval val; \
        ZVAL_LONG(&val, value[i]); \
        zend_hash_index_update(ht, i, &val); \
    } \
    zval arr; \
    ZVAL_ARR(&arr, ht); \
    zend_declare_class_constant(class_entry, name, sizeof(name)-1, &arr); \
    } while (0)

#endif //EXT_POCKETMINE_MATH_ZENDUTIL_H
