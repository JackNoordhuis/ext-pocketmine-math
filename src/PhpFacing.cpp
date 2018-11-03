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

/* PHP-Land Facing class */

PHP_CLASS_ENTRY(PhpFacing);

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_Facing_axis, 0, 1, IS_LONG, 0)
    ZEND_ARG_TYPE_INFO(0, direction, IS_LONG, 0)
ZEND_END_ARG_INFO()

PHP_CLASS_METHOD(PhpFacing, axis, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC) {
    zend_long direction = NULL;

    ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 1, 1)
        Z_PARAM_LONG(direction)
    ZEND_PARSE_PARAMETERS_END();

    RETURN_LONG(Facing::axis((int)direction));
}

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_Facing_isPositive, 0, 1, _IS_BOOL, 0)
    ZEND_ARG_TYPE_INFO(0, direction, IS_LONG, 0)
ZEND_END_ARG_INFO()

PHP_CLASS_METHOD(PhpFacing, isPositive, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC) {
    zend_long direction = NULL;

    ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 1, 1)
        Z_PARAM_LONG(direction)
    ZEND_PARSE_PARAMETERS_END();

    RETURN_BOOL(Facing::isPositive((int)direction));
}

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_Facing_opposite, 0, 1, IS_LONG, 0)
    ZEND_ARG_TYPE_INFO(0, direction, IS_LONG, 0)
ZEND_END_ARG_INFO()

PHP_CLASS_METHOD(PhpFacing, opposite, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC) {
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

PHP_CLASS_METHOD(PhpFacing, rotate, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC) {
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

PHP_CLASS_METHOD(PhpFacing, validate, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC) {
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

void register_facing_class() {
    REGISTER_FUNCTION_ENTRY_START()
        REGISTER_FUNCTION_ENTRY(PhpFacing, axis, arginfo_Facing_axis)
        REGISTER_FUNCTION_ENTRY(PhpFacing, isPositive, arginfo_Facing_isPositive)
        REGISTER_FUNCTION_ENTRY(PhpFacing, opposite, arginfo_Facing_opposite)
        REGISTER_FUNCTION_ENTRY(PhpFacing, rotate, arginfo_Facing_rotate)
        REGISTER_FUNCTION_ENTRY(PhpFacing, validate, arginfo_Facing_validate)
    REGISTER_FUNCTION_ENTRY_END();

    REGISTER_CLASS_SET_ENTRY(Facing, "pocketmine\\math\\Facing", PhpFacing);

    REGISTER_CLASS_CONST_LONG(PhpFacing_entry, "AXIS_Y", Facing::AXIS_Y);
    REGISTER_CLASS_CONST_LONG(PhpFacing_entry, "AXIS_Z", Facing::AXIS_Z);
    REGISTER_CLASS_CONST_LONG(PhpFacing_entry, "AXIS_X", Facing::AXIS_X);

    REGISTER_CLASS_CONST_LONG(PhpFacing_entry, "FLAG_AXIS_POSITIVE", Facing::FLAG_AXIS_POSITIVE);

    REGISTER_CLASS_CONST_LONG(PhpFacing_entry, "DOWN", Facing::DOWN);
    REGISTER_CLASS_CONST_LONG(PhpFacing_entry, "UP", Facing::UP);
    REGISTER_CLASS_CONST_LONG(PhpFacing_entry, "NORTH", Facing::NORTH);
    REGISTER_CLASS_CONST_LONG(PhpFacing_entry, "SOUTH", Facing::SOUTH);
    REGISTER_CLASS_CONST_LONG(PhpFacing_entry, "WEST", Facing::WEST);
    REGISTER_CLASS_CONST_LONG(PhpFacing_entry, "EAST", Facing::EAST);

    REGISTER_CLASS_CONST_LONG_ARRAY(PhpFacing_entry, "ALL", Facing::ALL);
    REGISTER_CLASS_CONST_LONG_ARRAY(PhpFacing_entry, "HORIZONTAL", Facing::HORIZONTAL);
}