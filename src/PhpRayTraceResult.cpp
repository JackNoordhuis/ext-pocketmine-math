//
// Created by Jack Noordhuis on 11/11/18.
//

#include "PhpRayTraceResult.h"

#include "lib/RayTraceResult.h"

// Defines so we can use our macros in ZendUtil.h.
#define CLASS_TYPE RayTraceResult


/* PHP-Land RayTraceResult class */

PHP_CLASS_ENTRY_EX();

ZEND_BEGIN_ARG_INFO_EX(ARG_INFO_NAME(__construct), 0, 0, 3)
    ZEND_ARG_OBJ_INFO(0, bb, pocketmine\\math\\AxisAlignedBB, 0)
    ZEND_ARG_TYPE_INFO(0, hitface, IS_LONG, 0)
    ZEND_ARG_OBJ_INFO(0, hitVector, pocketmine\\math\\Vector3, 0)
ZEND_END_ARG_INFO()

PHP_CLASS_METHOD_EX(__construct, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR) {
    zval *bb = NULL;
    zend_long hitFace = 0;
    zval *hitVector = NULL;

    ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 3, 3)
        Z_PARAM_OBJECT(bb)
        Z_PARAM_LONG(hitFace)
        Z_PARAM_OBJECT(hitVector)
    ZEND_PARSE_PARAMETERS_END();

    UPDATE_CLASS_PROPERTY("bb", bb);
    UPDATE_CLASS_PROPERTY_LONG("hitFace", hitFace);
    UPDATE_CLASS_PROPERTY("hitVector", hitVector);

    SET_PHP_OBJECT_CONTAINER(new RayTraceResult(FETCH_PHP_OBJECT_CONTAINER_OTHER_EX(AxisAlignedBB, bb), (int)hitFace, FETCH_PHP_OBJECT_CONTAINER_OTHER_EX(Vector3, hitVector)));
}

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO(ARG_INFO_NAME(getBoundingBox), pocketmine\\math\\AxisAlignedBB, 0)
ZEND_END_ARG_INFO()

PHP_CLASS_METHOD_EX(getBoundingBox, ZEND_ACC_PUBLIC) {
    zend_parse_parameters_none_throw();

    zval *rv, *result;
    RETURN_ZVAL(zend_read_property(PhpRayTraceResult_entry, getThis(), "bb", sizeof("bb")-1, 0, rv), 0, 1);
}

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO(ARG_INFO_NAME(getHitFace), IS_LONG, 0)
ZEND_END_ARG_INFO()

PHP_CLASS_METHOD_EX(getHitFace, ZEND_ACC_PUBLIC) {
    zend_parse_parameters_none_throw();

    zval *rv;
    RETURN_ZVAL(zend_read_property(PhpRayTraceResult_entry, getThis(), "hitFace", sizeof("hitFace")-1, IS_FALSE, rv), 0, 1);

}

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO(ARG_INFO_NAME(getHitVector), pocketmine\\math\\Vector3, 0)
ZEND_END_ARG_INFO()

PHP_CLASS_METHOD_EX(getHitVector, ZEND_ACC_PUBLIC) {
    zend_parse_parameters_none_throw();

    zval *rv;
    RETURN_ZVAL(zend_read_property(PhpRayTraceResult_entry, getThis(), "hitVector", sizeof("hitVector")-1, IS_FALSE, rv), 0, 1);

}

void register_raytraceresult_class() {
    REGISTER_FUNCTION_ENTRY_START()
        REGISTER_FUNCTION_ENTRY(__construct)
        REGISTER_FUNCTION_ENTRY(getBoundingBox)
        REGISTER_FUNCTION_ENTRY(getHitFace)
        REGISTER_FUNCTION_ENTRY(getHitVector)
    REGISTER_FUNCTION_ENTRY_END();

    REGISTER_CLASS_WITH_HANDLERS_SET_ENTRY("pocketmine\\math\\RayTraceResult");

    REGISTER_CLASS_PROPERTY("bb", ZEND_ACC_PUBLIC);
    REGISTER_CLASS_PROPERTY_LONG("hitFace", ZEND_ACC_PUBLIC);
    REGISTER_CLASS_PROPERTY("hitVector", ZEND_ACC_PUBLIC);
}

// Undefine so we can use the macros for other classes.
#undef CLASS_TYPE