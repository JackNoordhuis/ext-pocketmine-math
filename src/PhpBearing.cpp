//
// Created by Jack Noordhuis on 2/11/18.
//

#include "PhpBearing.h"

#include "lib/Bearing.h"

#include <stdexcept>

extern "C" {
#include "Zend/zend_exceptions.h"
#include "ext/spl/spl_exceptions.h"
}

// Defines so we can use our macros in ZendUtil.h.
#define CLASS_TYPE Bearing


/* PHP-Land Bearing class */

PHP_CLASS_ENTRY();

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_Bearing_toFacing, 0, 1, IS_LONG, 0)
    ZEND_ARG_TYPE_INFO(0, bearing, IS_LONG, 0)
ZEND_END_ARG_INFO()

PHP_CLASS_METHOD_EX(toFacing, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC) {
    zend_long bearing = NULL;

    int result;

    ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 1, 1)
        Z_PARAM_LONG(bearing)
    ZEND_PARSE_PARAMETERS_END();

    try {
        result = Bearing::toFacing((int)bearing);
    } catch(std::invalid_argument &e) {
        zend_throw_exception_ex(spl_ce_InvalidArgumentException, 0, e.what());
        return;
    }

    RETURN_LONG(result);
}

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_Bearing_fromFacing, 0, 1, IS_LONG, 0)
    ZEND_ARG_TYPE_INFO(0, facing, IS_LONG, 0)
ZEND_END_ARG_INFO()

PHP_CLASS_METHOD_EX(fromFacing, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC) {
    zend_long facing = NULL;

    int result;

    ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 1, 1)
        Z_PARAM_LONG(facing)
    ZEND_PARSE_PARAMETERS_END();

    try {
        result = Bearing::fromFacing((int)facing);
    } catch(std::invalid_argument &e) {
        zend_throw_exception_ex(spl_ce_InvalidArgumentException, 0, e.what());
        return;
    }

    RETURN_LONG(result);
}

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_Bearing_fromAngle, 0, 1, IS_LONG, 0)
    ZEND_ARG_TYPE_INFO(0, angle, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

PHP_CLASS_METHOD_EX(fromAngle, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC) {
    double angle = 0;

    ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 1, 1)
        Z_PARAM_DOUBLE(angle)
    ZEND_PARSE_PARAMETERS_END();

    RETURN_LONG(Bearing::fromAngle(angle));
}

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_Bearing_rotate, 0, 2, IS_LONG, 0)
    ZEND_ARG_TYPE_INFO(0, bearing, IS_LONG, 0)
    ZEND_ARG_TYPE_INFO(0, step, IS_LONG, 0)
ZEND_END_ARG_INFO()

PHP_CLASS_METHOD_EX(rotate, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC) {
    zend_long bearing = NULL;
    zend_long step = NULL;

    ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 2, 2)
        Z_PARAM_LONG(bearing)
        Z_PARAM_LONG(step)
    ZEND_PARSE_PARAMETERS_END();

    RETURN_LONG(Bearing::rotate((int)bearing, (int)step));
}

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO(arginfo_Bearing_opposite, IS_LONG, 0)
    ZEND_ARG_TYPE_INFO(0, bearing, IS_LONG, 0)
ZEND_END_ARG_INFO()

PHP_CLASS_METHOD_EX(opposite, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC) {
    zend_long bearing = NULL;

    ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 1, 1)
        Z_PARAM_LONG(bearing)
    ZEND_PARSE_PARAMETERS_END();

    RETURN_LONG(Bearing::opposite(bearing));
}

void register_bearing_class() {
    REGISTER_FUNCTION_ENTRY_START()
        REGISTER_FUNCTION_ENTRY(toFacing)
        REGISTER_FUNCTION_ENTRY(fromFacing)
        REGISTER_FUNCTION_ENTRY(fromAngle)
        REGISTER_FUNCTION_ENTRY(rotate)
        REGISTER_FUNCTION_ENTRY(opposite)
    REGISTER_FUNCTION_ENTRY_END();

    REGISTER_CLASS_SET_ENTRY("pocketmine\\math\\Bearing");

    REGISTER_CLASS_CONST_LONG("SOUTH", Bearing::SOUTH);
    REGISTER_CLASS_CONST_LONG("WEST", Bearing::WEST);
    REGISTER_CLASS_CONST_LONG("NORTH", Bearing::NORTH);
    REGISTER_CLASS_CONST_LONG("EAST", Bearing::EAST);
}

// Undefine so we can use the macros for other classes.
#undef CLASS_TYPE