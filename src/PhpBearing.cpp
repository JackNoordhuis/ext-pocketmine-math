//
// Created by Jack Noordhuis on 2/11/18.
//

#include "PhpBearing.h"

#include "ZendUtil.h"

#include "lib/Bearing.h"

#include <stdexcept>
#include <string>

extern "C" {
#include "php.h"
#include "Zend/zend_exceptions.h"
#include "ext/spl/spl_exceptions.h"
}

zend_class_entry *bearing_entry;

/* PHP-Land Bearing class */

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_Bearing_toFacing, 0, 1, IS_LONG, 0)
    ZEND_ARG_TYPE_INFO(0, bearing, IS_LONG, 0)
ZEND_END_ARG_INFO()

PHP_METHOD(PhpBearing, toFacing) {
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

PHP_METHOD(PhpBearing, fromFacing) {
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

PHP_METHOD(PhpBearing, fromAngle) {
    double angle = NULL;

    ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 1, 1)
        Z_PARAM_DOUBLE(angle)
    ZEND_PARSE_PARAMETERS_END();

    RETURN_LONG(Bearing::fromAngle(angle));
}

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_Bearing_rotate, 0, 2, IS_LONG, 0)
    ZEND_ARG_TYPE_INFO(0, bearing, IS_LONG, 0)
    ZEND_ARG_TYPE_INFO(0, step, IS_LONG, 0)
ZEND_END_ARG_INFO()

PHP_METHOD(PhpBearing, rotate) {
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

PHP_METHOD(PhpBearing, opposite) {
    zend_long bearing = NULL;

    ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 1, 1)
        Z_PARAM_LONG(bearing)
    ZEND_PARSE_PARAMETERS_END();

    RETURN_LONG(Bearing::opposite(bearing));
}

zend_function_entry bearing_class_methods[] = {
        PHP_ME(PhpBearing, toFacing, arginfo_Bearing_toFacing, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
        PHP_ME(PhpBearing, fromFacing, arginfo_Bearing_fromFacing, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
        PHP_ME(PhpBearing, fromAngle, arginfo_Bearing_fromAngle, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
        PHP_ME(PhpBearing, rotate, arginfo_Bearing_rotate, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
        PHP_ME(PhpBearing, opposite, arginfo_Bearing_opposite, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
        PHP_FE_END
};

void register_bearing_class() {
    zend_class_entry ce;
    INIT_CLASS_ENTRY(ce, "pocketmine\\math\\Bearing", bearing_class_methods);

    bearing_entry = zend_register_internal_class(&ce);

    REGISTER_CLASS_CONST_LONG(bearing_entry, "SOUTH", Bearing::SOUTH);
    REGISTER_CLASS_CONST_LONG(bearing_entry, "WEST", Bearing::WEST);
    REGISTER_CLASS_CONST_LONG(bearing_entry, "NORTH", Bearing::NORTH);
    REGISTER_CLASS_CONST_LONG(bearing_entry, "EAST", Bearing::EAST);
}