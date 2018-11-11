//
// Created by Jack Noordhuis on 6/11/18.
//

#include "PhpMath.h"

#include "lib/Math.h"

// Defines so we can use our macros in ZendUtil.h.
#define CLASS_TYPE Math


/* PHP-Land Math class */

PHP_CLASS_ENTRY();

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(ARG_INFO_NAME(floorFloat), 0, 1, IS_LONG, 0)
    ZEND_ARG_TYPE_INFO(0, n, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

PHP_CLASS_METHOD_EX(floorFloat, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC) {
    double n = 0;

    ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 1, 1)
            Z_PARAM_DOUBLE(n)
    ZEND_PARSE_PARAMETERS_END();

    RETURN_LONG(Math::floorFloat(n));
}

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(ARG_INFO_NAME(ceilFloat), 0, 1, IS_LONG, 0)
    ZEND_ARG_TYPE_INFO(0, n, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

PHP_CLASS_METHOD_EX(ceilFloat, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC) {
    double n = 0;

    ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 1, 1)
        Z_PARAM_DOUBLE(n)
    ZEND_PARSE_PARAMETERS_END();

    RETURN_LONG(Math::ceilFloat(n));
}

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(ARG_INFO_NAME(solveQuadratic), 0, 3, IS_ARRAY, 0)
    ZEND_ARG_TYPE_INFO(0, a, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(0, b, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(0, c, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

PHP_CLASS_METHOD_EX(solveQuadratic, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC) {
    double a = 0;
    double b = 0;
    double c = 0;

    ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 3, 3)
        Z_PARAM_DOUBLE(a)
        Z_PARAM_DOUBLE(b)
        Z_PARAM_DOUBLE(c)
    ZEND_PARSE_PARAMETERS_END();

    std::vector<double> results = Math::solveQuadratic(a, b, c);

    HashTable *ht;
    ALLOC_HASHTABLE(ht);
    int value_len = results.size();
    zend_hash_init(ht, value_len, NULL, NULL, 0);
    for(int i = 0; i < value_len; ++i) {
        zval val;
        ZVAL_DOUBLE(&val, results[i]);
        zend_hash_index_update(ht, i, &val);
    }

    ZVAL_ARR(return_value, ht);
}

void register_math_class() {
    REGISTER_FUNCTION_ENTRY_START()
        REGISTER_FUNCTION_ENTRY(floorFloat)
        REGISTER_FUNCTION_ENTRY(ceilFloat)
        REGISTER_FUNCTION_ENTRY(solveQuadratic)
    REGISTER_FUNCTION_ENTRY_END();

    REGISTER_CLASS_SET_ENTRY("pocketmine\\math\\Math");

    PhpMath_entry->ce_flags = ZEND_ACC_ABSTRACT;
}

// Undefine so we can use the macros for other classes.
#undef CLASS_TYPE