//
// Created by Jack Noordhuis on 1/11/18.
//

#include "PhpFacing.h"

#include "lib/Facing.h"

#include <stdexcept>

extern "C" {
#include "Zend/zend_exceptions.h"
#include "ext/spl/spl_exceptions.h"
}

// Defines so we can use our macros in ZendUtil.h.
#define CLASS_TYPE Facing

/* PHP-Land Facing class */

PHP_CLASS_ENTRY();

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_Facing_axis, 0, 1, IS_LONG, 0)
    ZEND_ARG_TYPE_INFO(0, direction, IS_LONG, 0)
ZEND_END_ARG_INFO()

PHP_CLASS_METHOD_EX(axis, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC) {
    zend_long direction = NULL;

    ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 1, 1)
        Z_PARAM_LONG(direction)
    ZEND_PARSE_PARAMETERS_END();

    RETURN_LONG(Facing::axis((int) direction));
}

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_Facing_isPositive, 0, 1, _IS_BOOL, 0)
    ZEND_ARG_TYPE_INFO(0, direction, IS_LONG, 0)
ZEND_END_ARG_INFO()

PHP_CLASS_METHOD_EX(isPositive, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC) {
    zend_long direction = NULL;

    ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 1, 1)
        Z_PARAM_LONG(direction)
    ZEND_PARSE_PARAMETERS_END();

    RETURN_BOOL(Facing::isPositive((int) direction));
}

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_Facing_opposite, 0, 1, IS_LONG, 0)
    ZEND_ARG_TYPE_INFO(0, direction, IS_LONG, 0)
ZEND_END_ARG_INFO()

PHP_CLASS_METHOD_EX(opposite, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC) {
    zend_long direction = NULL;

    ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 1, 1)
        Z_PARAM_LONG(direction)
    ZEND_PARSE_PARAMETERS_END();

    RETURN_LONG(Facing::opposite((int) direction));
}

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_Facing_rotate, 0, 3, IS_LONG, 0)
    ZEND_ARG_TYPE_INFO(0, direction, IS_LONG, 0)
    ZEND_ARG_TYPE_INFO(0, axis, IS_LONG, 0)
    ZEND_ARG_TYPE_INFO(0, clockwise, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

PHP_CLASS_METHOD_EX(rotate, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC) {
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
        result = Facing::rotate((int) direction, (int) axis, clockwise);
    } catch (std::invalid_argument &e) {
        zend_throw_exception_ex(spl_ce_InvalidArgumentException, 0, e.what());
        return;
    }

    RETURN_LONG(result);
}

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO(arginfo_Facing_validate, IS_VOID, 0)
    ZEND_ARG_TYPE_INFO(0, facing, IS_LONG, 0)
ZEND_END_ARG_INFO()

PHP_CLASS_METHOD_EX(validate, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC) {
    zend_long facing = NULL;

    ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 1, 1)
        Z_PARAM_LONG(facing)
    ZEND_PARSE_PARAMETERS_END();

    try {
        Facing::validate((int) facing);
    } catch (std::invalid_argument &e) {
        zend_throw_exception_ex(spl_ce_InvalidArgumentException, 0, e.what());
        return;
    }
}

void register_facing_class() {
    REGISTER_FUNCTION_ENTRY_START()
        REGISTER_FUNCTION_ENTRY(axis)
        REGISTER_FUNCTION_ENTRY(isPositive)
        REGISTER_FUNCTION_ENTRY(opposite)
        REGISTER_FUNCTION_ENTRY(rotate)
        REGISTER_FUNCTION_ENTRY(validate)
    REGISTER_FUNCTION_ENTRY_END();

    REGISTER_CLASS_SET_ENTRY("pocketmine\\math\\Facing");

    REGISTER_CLASS_CONST_LONG("AXIS_Y", Facing::AXIS_Y);
    REGISTER_CLASS_CONST_LONG("AXIS_Z", Facing::AXIS_Z);
    REGISTER_CLASS_CONST_LONG("AXIS_X", Facing::AXIS_X);

    REGISTER_CLASS_CONST_LONG("FLAG_AXIS_POSITIVE", Facing::FLAG_AXIS_POSITIVE);

    REGISTER_CLASS_CONST_LONG("DOWN", Facing::DOWN);
    REGISTER_CLASS_CONST_LONG("UP", Facing::UP);
    REGISTER_CLASS_CONST_LONG("NORTH", Facing::NORTH);
    REGISTER_CLASS_CONST_LONG("SOUTH", Facing::SOUTH);
    REGISTER_CLASS_CONST_LONG("WEST", Facing::WEST);
    REGISTER_CLASS_CONST_LONG("EAST", Facing::EAST);

//    TODO: Fix this
//    don't register arrays as constats, they cause too many issues
//    REGISTER_CLASS_CONST_LONG_ARRAY("ALL", Facing::ALL);
//    REGISTER_CLASS_CONST_LONG_ARRAY("HORIZONTAL", Facing::HORIZONTAL);
}

// Undefine so we can use the macros for other classes.
#undef CLASS_TYPE