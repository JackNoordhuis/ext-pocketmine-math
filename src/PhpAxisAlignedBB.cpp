//
// Created by Jack Noordhuis on 12/11/18.
//

#include "PhpAxisAlignedBB.h"

#include "PhpRayTraceResult.h"
#include "PhpVector3.h"

#include "lib/AxisAlignedBB.h"
#include "lib/Vector3.h"
#include "lib/RayTraceResult.h"

#include <stdexcept>
#include <string>

extern "C" {
#include "Zend/zend_exceptions.h"
#include "ext/spl/spl_exceptions.h"
}

// Defines so we can use our macros in ZendUtil.h.
#define CLASS_TYPE AxisAlignedBB

#define UPDATE_PROPERTIES() \
    UPDATE_CLASS_PROPERTY_DOUBLE("minX", minX); \
    UPDATE_CLASS_PROPERTY_DOUBLE("minY", minY); \
    UPDATE_CLASS_PROPERTY_DOUBLE("minZ", minZ); \
    UPDATE_CLASS_PROPERTY_DOUBLE("maxX", maxX); \
    UPDATE_CLASS_PROPERTY_DOUBLE("maxY", maxY); \
    UPDATE_CLASS_PROPERTY_DOUBLE("maxZ", maxZ)

#define UPDATE_PROPERTIES_INTERN_OTHER(obj) \
    UPDATE_CLASS_PROPERTY_DOUBLE_OTHER(obj, "minX", intern->container->minX); \
    UPDATE_CLASS_PROPERTY_DOUBLE_OTHER(obj, "minY", intern->container->minY); \
    UPDATE_CLASS_PROPERTY_DOUBLE_OTHER(obj, "minZ", intern->container->minZ); \
    UPDATE_CLASS_PROPERTY_DOUBLE_OTHER(obj, "maxX", intern->container->maxX); \
    UPDATE_CLASS_PROPERTY_DOUBLE_OTHER(obj, "maxY", intern->container->maxY); \
    UPDATE_CLASS_PROPERTY_DOUBLE_OTHER(obj, "maxZ", intern->container->maxZ)

#define UPDATE_PROPERTIES_CONTAINER() \
    UPDATE_CLASS_PROPERTY_DOUBLE("minX", container->minX); \
    UPDATE_CLASS_PROPERTY_DOUBLE("minY", container->minY); \
    UPDATE_CLASS_PROPERTY_DOUBLE("minZ", container->minZ); \
    UPDATE_CLASS_PROPERTY_DOUBLE("maxX", container->maxX); \
    UPDATE_CLASS_PROPERTY_DOUBLE("maxY", container->maxY); \
    UPDATE_CLASS_PROPERTY_DOUBLE("maxZ", container->maxZ)


/* PHP-Land AxisAlignedBB class */

PHP_CLASS_ENTRY_EX();

ZEND_BEGIN_ARG_INFO_EX(ARG_INFO_NAME(__construct), 0, 0, 6)
    ZEND_ARG_TYPE_INFO(0, minX, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(0, minY, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(0, minZ, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(0, maxX, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(0, maxY, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(0, maxZ, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

PHP_CLASS_METHOD_EX(__construct, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR) {
    double minX = 0, minY = 0, minZ = 0, maxX = 0, maxY = 0, maxZ = 0;

    ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 6, 6)
        Z_PARAM_DOUBLE(minX)
        Z_PARAM_DOUBLE(minY)
        Z_PARAM_DOUBLE(minZ)
        Z_PARAM_DOUBLE(maxX)
        Z_PARAM_DOUBLE(maxY)
        Z_PARAM_DOUBLE(maxZ)
    ZEND_PARSE_PARAMETERS_END();

    UPDATE_PROPERTIES();

    SET_PHP_OBJECT_CONTAINER(new AxisAlignedBB(minX, minY, minZ, maxX, maxY, maxZ));
}

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(ARG_INFO_NAME(setBounds), 0, 6, pocketmine\\math\\AxisAlignedBB, 0)
    ZEND_ARG_TYPE_INFO(0, minX, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(0, minY, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(0, minZ, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(0, maxX, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(0, maxY, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(0, maxZ, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

PHP_CLASS_METHOD_EX(setBounds, ZEND_ACC_PUBLIC) {
    double minX = 0, minY = 0, minZ = 0, maxX = 0, maxY = 0, maxZ = 0;

    ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 6, 6)
        Z_PARAM_DOUBLE(minX)
        Z_PARAM_DOUBLE(minY)
        Z_PARAM_DOUBLE(minZ)
        Z_PARAM_DOUBLE(maxX)
        Z_PARAM_DOUBLE(maxY)
        Z_PARAM_DOUBLE(maxZ)
    ZEND_PARSE_PARAMETERS_END();

    try {
        FETCH_PHP_OBJECT_CONTAINER()->setBounds(minX, minY, minZ, maxX, maxY, maxZ);
    } catch(std::invalid_argument &e) {
        zend_throw_exception_ex(spl_ce_InvalidArgumentException, 0, e.what());
    }

    UPDATE_PROPERTIES();

    RETURN_ZVAL(getThis(), 0, 1);
}

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(ARG_INFO_NAME(setBB), 0, 1, pocketmine\\math\\AxisAlignedBB, 0)
    ZEND_ARG_OBJ_INFO(0, bb, pocketmine\\math\\AxisAlignedBB, 0)
ZEND_END_ARG_INFO()

PHP_CLASS_METHOD_EX(setBB, ZEND_ACC_PUBLIC) {
    zval *bb = NULL;

    ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 6, 6)
        Z_PARAM_OBJECT(bb);
    ZEND_PARSE_PARAMETERS_END();

    FETCH_PHP_OBJECT_CONTAINER_VAR(container);

    container->setBB(FETCH_PHP_OBJECT_CONTAINER_OTHER(bb));

    UPDATE_PROPERTIES_CONTAINER();

    RETURN_ZVAL(getThis(), 0, 1);
}

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(ARG_INFO_NAME(addCoord), 0, 3, pocketmine\\math\\AxisAlignedBB, 0)
    ZEND_ARG_TYPE_INFO(0, x, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(0, y, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(0, z, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

PHP_CLASS_METHOD_EX(addCoord, ZEND_ACC_PUBLIC) {
    double x = 0, y = 0, z = 0;

    ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 3, 3)
        Z_PARAM_DOUBLE(x)
        Z_PARAM_DOUBLE(y)
        Z_PARAM_DOUBLE(z)
    ZEND_PARSE_PARAMETERS_END();

    FETCH_PHP_OBJECT_CONTAINER_VAR(container);

    object_init_ex(return_value, PhpAxisAlignedBB_entry);
    FETCH_PHP_OBJECT_VAR_OTHER(intern, return_value);
    intern->container = container->addCoord(x, y, z);

    UPDATE_PROPERTIES_INTERN_OTHER(return_value);

    RETURN_ZVAL(return_value, 0, 1);
}

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(ARG_INFO_NAME(expand), 0, 3, pocketmine\\math\\AxisAlignedBB, 0)
    ZEND_ARG_TYPE_INFO(0, x, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(0, y, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(0, z, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

PHP_CLASS_METHOD_EX(expand, ZEND_ACC_PUBLIC) {
    double x = 0, y = 0, z = 0;

    ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 3, 3)
        Z_PARAM_DOUBLE(x)
        Z_PARAM_DOUBLE(y)
        Z_PARAM_DOUBLE(z)
    ZEND_PARSE_PARAMETERS_END();

    FETCH_PHP_OBJECT_CONTAINER_VAR(container);

    container->expand(x, y, z);

    UPDATE_PROPERTIES_CONTAINER();

    RETURN_ZVAL(getThis(), 0, 1);
}

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(ARG_INFO_NAME(expandedCopy), 0, 3, pocketmine\\math\\AxisAlignedBB, 0)
    ZEND_ARG_TYPE_INFO(0, x, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(0, y, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(0, z, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

PHP_CLASS_METHOD_EX(expandedCopy, ZEND_ACC_PUBLIC) {
    double x = 0, y = 0, z = 0;

    ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 3, 3)
        Z_PARAM_DOUBLE(x)
        Z_PARAM_DOUBLE(y)
        Z_PARAM_DOUBLE(z)
    ZEND_PARSE_PARAMETERS_END();

    FETCH_PHP_OBJECT_CONTAINER_VAR(container);

    object_init_ex(return_value, PhpAxisAlignedBB_entry);
    FETCH_PHP_OBJECT_VAR_OTHER(intern, return_value);
    intern->container = container->expandedCopy(x, y, z);

    UPDATE_PROPERTIES_INTERN_OTHER(return_value);
}

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(ARG_INFO_NAME(offset), 0, 3, pocketmine\\math\\AxisAlignedBB, 0)
    ZEND_ARG_TYPE_INFO(0, x, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(0, y, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(0, z, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

PHP_CLASS_METHOD_EX(offset, ZEND_ACC_PUBLIC) {
    double x = 0, y = 0, z = 0;

    ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 3, 3)
        Z_PARAM_DOUBLE(x)
        Z_PARAM_DOUBLE(y)
        Z_PARAM_DOUBLE(z)
    ZEND_PARSE_PARAMETERS_END();

    FETCH_PHP_OBJECT_CONTAINER_VAR(container);

    container->offset(x, y, z);

    UPDATE_PROPERTIES_CONTAINER();

    RETURN_ZVAL(getThis(), 0, 1);
}

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(ARG_INFO_NAME(offsetCopy), 0, 3, pocketmine\\math\\AxisAlignedBB, 0)
    ZEND_ARG_TYPE_INFO(0, x, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(0, y, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(0, z, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

PHP_CLASS_METHOD_EX(offsetCopy, ZEND_ACC_PUBLIC) {
    double x = 0, y = 0, z = 0;

    ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 3, 3)
        Z_PARAM_DOUBLE(x)
        Z_PARAM_DOUBLE(y)
        Z_PARAM_DOUBLE(z)
    ZEND_PARSE_PARAMETERS_END();

    FETCH_PHP_OBJECT_CONTAINER_VAR(container);

    object_init_ex(return_value, PhpAxisAlignedBB_entry);
    FETCH_PHP_OBJECT_VAR_OTHER(intern, return_value);
    intern->container = container->offsetCopy(x, y, z);

    UPDATE_PROPERTIES_INTERN_OTHER(return_value);
}

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(ARG_INFO_NAME(contract), 0, 3, pocketmine\\math\\AxisAlignedBB, 0)
    ZEND_ARG_TYPE_INFO(0, x, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(0, y, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(0, z, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

PHP_CLASS_METHOD_EX(contract, ZEND_ACC_PUBLIC) {
    double x = 0, y = 0, z = 0;

    ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 3, 3)
        Z_PARAM_DOUBLE(x)
        Z_PARAM_DOUBLE(y)
        Z_PARAM_DOUBLE(z)
    ZEND_PARSE_PARAMETERS_END();

    FETCH_PHP_OBJECT_CONTAINER_VAR(container);

    container->contract(x, y, z);

    UPDATE_PROPERTIES_CONTAINER();

    RETURN_ZVAL(getThis(), 0, 1);
}

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(ARG_INFO_NAME(contractedCopy), 0, 3, pocketmine\\math\\AxisAlignedBB, 0)
    ZEND_ARG_TYPE_INFO(0, x, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(0, y, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(0, z, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

PHP_CLASS_METHOD_EX(contractedCopy, ZEND_ACC_PUBLIC) {
    double x = 0, y = 0, z = 0;

    ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 3, 3)
        Z_PARAM_DOUBLE(x)
        Z_PARAM_DOUBLE(y)
        Z_PARAM_DOUBLE(z)
    ZEND_PARSE_PARAMETERS_END();

    FETCH_PHP_OBJECT_CONTAINER_VAR(container);

    object_init_ex(return_value, PhpAxisAlignedBB_entry);
    FETCH_PHP_OBJECT_VAR_OTHER(intern, return_value);
    intern->container = container->contractCopy(x, y, z);

    UPDATE_PROPERTIES_INTERN_OTHER(return_value);
}

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(ARG_INFO_NAME(calculateXOffset), 0, 2, IS_DOUBLE, 0)
    ZEND_ARG_OBJ_INFO(0, bb, pocketmine\\math\\AxisAlignedBB, 0)
    ZEND_ARG_TYPE_INFO(0, x, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

PHP_CLASS_METHOD_EX(calculateXOffset, ZEND_ACC_PUBLIC) {
    zval *bb = NULL;
    double x = 0;

    ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 2, 2)
        Z_PARAM_OBJECT(bb)
        Z_PARAM_DOUBLE(x)
    ZEND_PARSE_PARAMETERS_END();

    FETCH_PHP_OBJECT_CONTAINER_VAR(container);
    FETCH_PHP_OBJECT_CONTAINER_VAR_OTHER(bb_container, bb);

    RETURN_DOUBLE(container->calculateZOffset(bb_container, x));
}

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(ARG_INFO_NAME(calculateYOffset), 0, 2, IS_DOUBLE, 0)
    ZEND_ARG_OBJ_INFO(0, bb, pocketmine\\math\\AxisAlignedBB, 0)
    ZEND_ARG_TYPE_INFO(0, y, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

PHP_CLASS_METHOD_EX(calculateYOffset, ZEND_ACC_PUBLIC) {
    zval *bb = NULL;
    double y = 0;

    ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 2, 2)
        Z_PARAM_OBJECT(bb)
        Z_PARAM_DOUBLE(y)
    ZEND_PARSE_PARAMETERS_END();

    FETCH_PHP_OBJECT_CONTAINER_VAR(container);
    FETCH_PHP_OBJECT_CONTAINER_VAR_OTHER(bb_container, bb);

    RETURN_DOUBLE(container->calculateYOffset(bb_container, y));
}

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(ARG_INFO_NAME(calculateZOffset), 0, 2, IS_DOUBLE, 0)
    ZEND_ARG_OBJ_INFO(0, bb, pocketmine\\math\\AxisAlignedBB, 0)
    ZEND_ARG_TYPE_INFO(0, z, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

PHP_CLASS_METHOD_EX(calculateZOffset, ZEND_ACC_PUBLIC) {
    zval *bb = NULL;
    double z = 0;

    ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 2, 2)
        Z_PARAM_OBJECT(bb)
        Z_PARAM_DOUBLE(z)
    ZEND_PARSE_PARAMETERS_END();

    FETCH_PHP_OBJECT_CONTAINER_VAR(container);
    FETCH_PHP_OBJECT_CONTAINER_VAR_OTHER(bb_container, bb);

    RETURN_DOUBLE(container->calculateZOffset(bb_container, z));
}

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(ARG_INFO_NAME(intersectsWith), 0, 1, _IS_BOOL, 0)
    ZEND_ARG_OBJ_INFO(0, bb, pocketmine\\math\\AxisAlignedBB, 0)
    ZEND_ARG_TYPE_INFO(0, epsilon, IS_DOUBLE, 1)
ZEND_END_ARG_INFO()

PHP_CLASS_METHOD_EX(intersectsWith, ZEND_ACC_PUBLIC) {
    zval *bb = NULL;
    double epsilon = 0.00001;

    ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 1, 2)
            Z_PARAM_OBJECT(bb)
            Z_PARAM_OPTIONAL
            Z_PARAM_DOUBLE(epsilon)
    ZEND_PARSE_PARAMETERS_END();

    FETCH_PHP_OBJECT_CONTAINER_VAR(container);
    FETCH_PHP_OBJECT_CONTAINER_VAR_OTHER(bb_container, bb);

    RETURN_BOOL(container->intersectsWith(bb_container, epsilon));
}

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(ARG_INFO_NAME(isVectorInside), 0, 1, _IS_BOOL, 0)
    ZEND_ARG_OBJ_INFO(0, bb, pocketmine\\math\\Vector3, 0)
ZEND_END_ARG_INFO()

PHP_CLASS_METHOD_EX(isVectorInside, ZEND_ACC_PUBLIC) {
    zval *vector = NULL;

    ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 1, 1)
        Z_PARAM_OBJECT(vector)
    ZEND_PARSE_PARAMETERS_END();

    FETCH_PHP_OBJECT_CONTAINER_VAR(container);
    FETCH_PHP_OBJECT_CONTAINER_VAR_OTHER_EX(Vector3, vector_container, vector);

    RETURN_BOOL(container->isVectorInside(vector_container));
}

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO(ARG_INFO_NAME(getAverageEdgeLength), IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

PHP_CLASS_METHOD_EX(getAverageEdgeLength, ZEND_ACC_PUBLIC) {
    zend_parse_parameters_none_throw();

    FETCH_PHP_OBJECT_CONTAINER_VAR(container);
    RETURN_DOUBLE(container->getAverageEdgeLength());
}

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(ARG_INFO_NAME(isVectorInYZ), 0, 1, _IS_BOOL, 0)
    ZEND_ARG_OBJ_INFO(0, bb, pocketmine\\math\\Vector3, 0)
ZEND_END_ARG_INFO()

PHP_CLASS_METHOD_EX(isVectorInYZ, ZEND_ACC_PUBLIC) {
    zval *vector = NULL;

    ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 1, 1)
        Z_PARAM_OBJECT(vector)
    ZEND_PARSE_PARAMETERS_END();

    FETCH_PHP_OBJECT_CONTAINER_VAR(container);
    FETCH_PHP_OBJECT_CONTAINER_VAR_OTHER_EX(Vector3, vector_container, vector);

    RETURN_BOOL(container->isVectorInYZ(vector_container));
}

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(ARG_INFO_NAME(isVectorInXZ), 0, 1, _IS_BOOL, 0)
    ZEND_ARG_OBJ_INFO(0, bb, pocketmine\\math\\Vector3, 0)
ZEND_END_ARG_INFO()

PHP_CLASS_METHOD_EX(isVectorInXZ, ZEND_ACC_PUBLIC) {
    zval *vector = NULL;

    ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 1, 1)
        Z_PARAM_OBJECT(vector)
    ZEND_PARSE_PARAMETERS_END();

    FETCH_PHP_OBJECT_CONTAINER_VAR(container);
    FETCH_PHP_OBJECT_CONTAINER_VAR_OTHER_EX(Vector3, vector_container, vector);

    RETURN_BOOL(container->isVectorInXZ(vector_container));
}

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(ARG_INFO_NAME(isVectorInXY), 0, 1, _IS_BOOL, 0)
    ZEND_ARG_OBJ_INFO(0, bb, pocketmine\\math\\Vector3, 0)
ZEND_END_ARG_INFO()

PHP_CLASS_METHOD_EX(isVectorInXY, ZEND_ACC_PUBLIC) {
    zval *vector = NULL;

    ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 1, 1)
        Z_PARAM_OBJECT(vector)
    ZEND_PARSE_PARAMETERS_END();

    FETCH_PHP_OBJECT_CONTAINER_VAR(container);
    FETCH_PHP_OBJECT_CONTAINER_VAR_OTHER_EX(Vector3, vector_container, vector);

    RETURN_BOOL(container->isVectorInXY(vector_container));
}

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(ARG_INFO_NAME(calculateIntercept), 0, 2, pocketmine\\math\\RayTraceResult, 1)
    ZEND_ARG_OBJ_INFO(0, pos1, pocketmine\\math\\Vector3, 0)
    ZEND_ARG_OBJ_INFO(0, pos2, pocketmine\\math\\Vector3, 0)
ZEND_END_ARG_INFO()

PHP_CLASS_METHOD_EX(calculateIntercept, ZEND_ACC_PUBLIC) {
    zval *pos1 = NULL, *pos2 = NULL;

    ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 2, 2)
        Z_PARAM_OBJECT(pos1)
        Z_PARAM_OBJECT(pos2)
    ZEND_PARSE_PARAMETERS_END();

    FETCH_PHP_OBJECT_CONTAINER_VAR(container);
    FETCH_PHP_OBJECT_CONTAINER_VAR_OTHER_EX(Vector3, pos1_container, pos1);
    FETCH_PHP_OBJECT_CONTAINER_VAR_OTHER_EX(Vector3, pos2_container, pos2);

    auto result = container->calculateIntercept(pos1_container, pos2_container);

    if(result == nullptr) {
        RETURN_NULL();
    }

    object_init_ex(return_value, raytraceresult_class_entry());
    FETCH_PHP_OBJECT_VAR_OTHER_EX(RayTraceResult, intern, return_value);
    intern->container = result;

    zval *vector;
    object_init_ex(vector, vector3_class_entry());
    FETCH_PHP_OBJECT_VAR_OTHER_EX(Vector3, vector_intern, vector);
    vector_intern->container = (Vector3 *)result->hitVector;

    UPDATE_CLASS_PROPERTY_OTHER(return_value, "bb", getThis());
    UPDATE_CLASS_PROPERTY_LONG_OTHER(return_value, "hitFace", result->hitFace);
    UPDATE_CLASS_PROPERTY_OTHER(return_value, "hitVector", vector);
}

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO(ARG_INFO_NAME(__toString), IS_STRING, 0)
ZEND_END_ARG_INFO()

PHP_CLASS_METHOD_EX(__toString, ZEND_ACC_PUBLIC) {
    zend_parse_parameters_none_throw();

    FETCH_PHP_OBJECT_CONTAINER_VAR(container);

    RETURN_STRING(std::string("AxisAlignedBB(" + std::to_string(container->minX) + ", " + std::to_string(container->minY) + ", " + std::to_string(container->minZ) + ", " + std::to_string(container->maxX) + ", " + std::to_string(container->maxY) + ", " + std::to_string(container->maxZ) + ")").c_str());
}

void register_axisalignedbb_class() {
    REGISTER_FUNCTION_ENTRY_START()
        REGISTER_FUNCTION_ENTRY(__construct)
        REGISTER_FUNCTION_ENTRY(setBounds)
        REGISTER_FUNCTION_ENTRY(setBB)
        REGISTER_FUNCTION_ENTRY(addCoord)
        REGISTER_FUNCTION_ENTRY(expand)
        REGISTER_FUNCTION_ENTRY(expandedCopy)
        REGISTER_FUNCTION_ENTRY(offset)
        REGISTER_FUNCTION_ENTRY(offsetCopy)
        REGISTER_FUNCTION_ENTRY(contract)
        REGISTER_FUNCTION_ENTRY(contractedCopy)
        REGISTER_FUNCTION_ENTRY(calculateXOffset)
        REGISTER_FUNCTION_ENTRY(calculateYOffset)
        REGISTER_FUNCTION_ENTRY(calculateZOffset)
        REGISTER_FUNCTION_ENTRY(intersectsWith)
        REGISTER_FUNCTION_ENTRY(isVectorInside)
        REGISTER_FUNCTION_ENTRY(getAverageEdgeLength)
        REGISTER_FUNCTION_ENTRY(isVectorInYZ)
        REGISTER_FUNCTION_ENTRY(isVectorInXZ)
        REGISTER_FUNCTION_ENTRY(isVectorInXY)
        REGISTER_FUNCTION_ENTRY(calculateIntercept)
        REGISTER_FUNCTION_ENTRY(__toString)
    REGISTER_FUNCTION_ENTRY_END();

    REGISTER_CLASS_WITH_HANDLERS_SET_ENTRY("pocketmine\\math\\AxisAlignedBB");

    REGISTER_CLASS_PROPERTY_DOUBLE("minX", ZEND_ACC_PUBLIC);
    REGISTER_CLASS_PROPERTY_DOUBLE("minY", ZEND_ACC_PUBLIC);
    REGISTER_CLASS_PROPERTY_DOUBLE("minZ", ZEND_ACC_PUBLIC);
    REGISTER_CLASS_PROPERTY_DOUBLE("maxX", ZEND_ACC_PUBLIC);
    REGISTER_CLASS_PROPERTY_DOUBLE("maxY", ZEND_ACC_PUBLIC);
    REGISTER_CLASS_PROPERTY_DOUBLE("maxZ", ZEND_ACC_PUBLIC);
}

// Undefine so we can use the macros for other classes.
#undef CLASS_TYPE