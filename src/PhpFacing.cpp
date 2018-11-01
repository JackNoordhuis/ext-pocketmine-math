//
// Created by Jack Noordhuis on 1/11/18.
//

#include "PhpFacing.h"

#include "ZendUtil.h"

#include "lib/Facing.h"

#include <stdexcept>
#include <string>

extern "C" {
#include "php.h"
#include "Zend/zend_exceptions.h"
#include "ext/spl/spl_exceptions.h"
}

zend_class_entry *facing_entry;

/* PHP-Land Facing class */

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_Facing_axis, 0, 1, IS_LONG, 0)
    ZEND_ARG_TYPE_INFO(0, direction, IS_LONG, 0)
ZEND_END_ARG_INFO()

PHP_METHOD(PhpFacing, axis) {
    zend_long direction = NULL;

    ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 1, 1)
        Z_PARAM_LONG(direction)
    ZEND_PARSE_PARAMETERS_END();

    RETURN_LONG(Facing::axis((int)direction));
}

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_Facing_isPositive, 0, 1, _IS_BOOL, 0)
    ZEND_ARG_TYPE_INFO(0, direction, IS_LONG, 0)
ZEND_END_ARG_INFO()

PHP_METHOD(PhpFacing, isPositive) {
    zend_long direction = NULL;

    ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 1, 1)
        Z_PARAM_LONG(direction)
    ZEND_PARSE_PARAMETERS_END();

    RETURN_BOOL(Facing::isPositive((int)direction));
}

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_Facing_opposite, 0, 1, IS_LONG, 0)
    ZEND_ARG_TYPE_INFO(0, direction, IS_LONG, 0)
ZEND_END_ARG_INFO()

PHP_METHOD(PhpFacing, opposite) {
    zend_long direction = NULL;

    ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 1, 1)
        Z_PARAM_LONG(direction)
    ZEND_PARSE_PARAMETERS_END();

    RETURN_LONG(Facing::opposite((int)direction));
}

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_Facing_rotate, 0, 3, IS_LONG, 0)
    ZEND_ARG_TYPE_INFO(0, direction, IS_LONG, 0)
    ZEND_ARG_TYPE_INFO(0, axis, IS_LONG, 0)
    ZEND_ARG_TYPE_INFO(0, clockwise, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

PHP_METHOD(PhpFacing, rotate) {
    zend_long direction = NULL;
    zend_long axis = NULL;
    zend_bool clockwise = NULL;

    int result;

    ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 3, 3)
        Z_PARAM_LONG(direction)
        Z_PARAM_LONG(axis)
        Z_PARAM_BOOL(clockwise)
    ZEND_PARSE_PARAMETERS_END();

    try {
        result = Facing::rotate((int)direction, (int)axis, clockwise);
    } catch(std::invalid_argument &e) {
        zend_throw_exception_ex(spl_ce_InvalidArgumentException, 0, e.what());
        return;
    }

    RETURN_LONG(result);
}

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO(arginfo_Facing_validate, IS_VOID, 0)
    ZEND_ARG_TYPE_INFO(0, facing, IS_LONG, 0)
ZEND_END_ARG_INFO()

PHP_METHOD(PhpFacing, validate) {
    zend_long facing = NULL;

    ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 1, 1)
        Z_PARAM_LONG(facing)
    ZEND_PARSE_PARAMETERS_END();

    try {
        Facing::validate((int)facing);
    } catch(std::invalid_argument &e) {
        zend_throw_exception_ex(spl_ce_InvalidArgumentException, 0, e.what());
        return;
    }
}

zend_function_entry facing_class_methods[] = {
    PHP_ME(PhpFacing, axis, arginfo_Facing_axis, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
    PHP_ME(PhpFacing, isPositive, arginfo_Facing_isPositive, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
    PHP_ME(PhpFacing, opposite, arginfo_Facing_opposite, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
    PHP_ME(PhpFacing, rotate, arginfo_Facing_rotate, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
    PHP_ME(PhpFacing, validate, arginfo_Facing_validate, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
    PHP_FE_END
};

void register_facing_class() {
    zend_class_entry ce;
    INIT_CLASS_ENTRY(ce, "pocketmine\\math\\Facing", facing_class_methods);

    facing_entry = zend_register_internal_class(&ce);

    zend_declare_class_constant_long(facing_entry, "AXIS_Y", sizeof("AXIS_Y")-1, Facing::AXIS_Y);
    zend_declare_class_constant_long(facing_entry, "AXIS_Z", sizeof("AXIS_Z")-1, Facing::AXIS_Z);
    zend_declare_class_constant_long(facing_entry, "AXIS_X", sizeof("AXIS_X")-1, Facing::AXIS_X);

    zend_declare_class_constant_long(facing_entry, "FLAG_AXIS_POSITIVE", sizeof("FLAG_AXIS_POSITIVE")-1, Facing::FLAG_AXIS_POSITIVE);

    zend_declare_class_constant_long(facing_entry, "DOWN", sizeof("DOWN")-1, Facing::DOWN);
    zend_declare_class_constant_long(facing_entry, "UP", sizeof("UP")-1, Facing::UP);
    zend_declare_class_constant_long(facing_entry, "NORTH", sizeof("NORTH")-1, Facing::NORTH);
    zend_declare_class_constant_long(facing_entry, "SOUTH", sizeof("SOUTH")-1, Facing::SOUTH);
    zend_declare_class_constant_long(facing_entry, "WEST", sizeof("WEST")-1, Facing::WEST);
    zend_declare_class_constant_long(facing_entry, "EAST", sizeof("EAST")-1, Facing::EAST);

    HashTable *all_ht;
    ALLOC_HASHTABLE(all_ht);
    zend_hash_init(all_ht, 6, NULL, NULL, 0);
    for(int i = 0; i < 6; ++i) {
        zval val;
        ZVAL_LONG(&val, Facing::ALL[i]);
        zend_hash_index_update(all_ht, i, &val);
    }

    zval all_arr;
    ZVAL_ARR(&all_arr, all_ht);
    zend_declare_class_constant(facing_entry, "ALL", sizeof("ALL")-1, &all_arr);

    HashTable *horizontal_ht;
    ALLOC_HASHTABLE(horizontal_ht);
    zend_hash_init(horizontal_ht, 4, NULL, NULL, 0);
    for(int i = 0; i < 4; ++i) {
        zval val;
        ZVAL_LONG(&val, Facing::HORIZONTAL[i]);
        zend_hash_index_update(horizontal_ht, i, &val);
    }

    zval horizontal_arr;
    ZVAL_ARR(&horizontal_arr, horizontal_ht);
    zend_declare_class_constant(facing_entry, "HORIZONTAL", sizeof("HORIZONTAL")-1, &horizontal_arr);
}