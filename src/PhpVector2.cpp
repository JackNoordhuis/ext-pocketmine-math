//
// Created by Jack Noordhuis on 2/11/18.
//

#include "PhpVector2.h"

#include "ZendUtil.h"

#include "lib/Vector2.h"

#include <string>

extern "C" {
#include "php.h"
}

/* PHP-Land Vector2 class */

PHP_CLASS_ENTRY_EX(PhpVector2, Vector2);

ZEND_BEGIN_ARG_INFO_EX(arginfo_Vector2___construct, 0, 0, 0)
    ZEND_ARG_TYPE_INFO(0, x, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(0, y, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

PHP_CLASS_METHOD(PhpVector2, __construct, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR) {
    double x = 0;
    double y = 0;

    ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 0, 2)
        Z_PARAM_OPTIONAL
        Z_PARAM_DOUBLE(x)
        Z_PARAM_OPTIONAL
        Z_PARAM_DOUBLE(y)
    ZEND_PARSE_PARAMETERS_END();

    auto vector = new Vector2(x, y);

    UPDATE_CLASS_PROPERTY_DOUBLE(PhpVector2_entry, "x", x);
    UPDATE_CLASS_PROPERTY_DOUBLE(PhpVector2_entry, "y", y);

    SET_PHP_OBJECT_CONTAINER(Vector2, vector);
}

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO(arginfo_Vector2_getX, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

PHP_CLASS_METHOD(PhpVector2, getX, ZEND_ACC_PUBLIC) {
    zend_parse_parameters_none_throw();

    RETURN_DOUBLE(FETCH_PHP_OBJECT_CONTAINER(Vector2)->getX());
}

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO(arginfo_Vector2_getY, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

PHP_CLASS_METHOD(PhpVector2, getY, ZEND_ACC_PUBLIC) {
    zend_parse_parameters_none_throw();

    RETURN_DOUBLE(FETCH_PHP_OBJECT_CONTAINER(Vector2)->getY());
}

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO(arginfo_Vector2_getFloorX, IS_LONG, 0)
ZEND_END_ARG_INFO()

PHP_CLASS_METHOD(PhpVector2, getFloorX, ZEND_ACC_PUBLIC) {
    zend_parse_parameters_none_throw();

    RETURN_LONG(FETCH_PHP_OBJECT_CONTAINER(Vector2)->getFloorX());
}

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO(arginfo_Vector2_getFloorY, IS_LONG, 0)
ZEND_END_ARG_INFO()

PHP_CLASS_METHOD(PhpVector2, getFloorY, ZEND_ACC_PUBLIC) {
    zend_parse_parameters_none_throw();

    RETURN_LONG(FETCH_PHP_OBJECT_CONTAINER(Vector2)->getFloorY());
}

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_Vector2_add, 0, 1, pocketmine\\math\\Vector2, 0)
    ZEND_ARG_INFO(0, x)
    ZEND_ARG_TYPE_INFO(0, y, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

PHP_CLASS_METHOD(PhpVector2, add, ZEND_ACC_PUBLIC) {
    zval *x = NULL;
    double y = 0;

    ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 1, 2)
        Z_PARAM_ZVAL(x)
        Z_PARAM_OPTIONAL
        Z_PARAM_DOUBLE(y)
    ZEND_PARSE_PARAMETERS_END();

    FETCH_PHP_OBJECT_CONTAINER_VAR(Vector2, container);

    zend_type type = Z_TYPE_P(x);
    if (type == IS_OBJECT or type == IS_LONG or type == IS_DOUBLE) {
        object_init_ex(return_value, PhpVector2_entry);
        FETCH_PHP_OBJECT_VAR_OTHER(Vector2, new_intern, return_value);
        if (type == IS_OBJECT) {
            FETCH_PHP_OBJECT_VAR_OTHER(Vector2, x_intern, x);
            if (zend_string_equals(x_intern->std.ce->name, PhpVector2_entry->name)) {
                new_intern->container = container->add(x_intern->container);
            } else {
                RETURN_NULL();
            }
        } else {
            new_intern->container = container->add(type == IS_DOUBLE ? Z_DVAL(*x) : Z_LVAL(*x), y);
        }

        UPDATE_CLASS_PROPERTY_DOUBLE_OTHER(PhpVector2_entry, return_value, "x", new_intern->container->x);
        UPDATE_CLASS_PROPERTY_DOUBLE_OTHER(PhpVector2_entry, return_value, "y", new_intern->container->y);
    }
}

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_Vector2_subtract, 0, 1, pocketmine\\math\\Vector2, 0)
    ZEND_ARG_INFO(0, x)
    ZEND_ARG_TYPE_INFO(0, y, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

PHP_CLASS_METHOD(PhpVector2, subtract, ZEND_ACC_PUBLIC) {
    zval *x = NULL;
    double y = 0;

    ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 1, 2)
        Z_PARAM_ZVAL(x)
        Z_PARAM_OPTIONAL
        Z_PARAM_DOUBLE(y)
    ZEND_PARSE_PARAMETERS_END();

    FETCH_PHP_OBJECT_CONTAINER_VAR(Vector2, container);

    zend_type type = Z_TYPE_P(x);
    if (type == IS_OBJECT or type == IS_LONG or type == IS_DOUBLE) {
        object_init_ex(return_value, PhpVector2_entry);
        FETCH_PHP_OBJECT_VAR_OTHER(Vector2, new_intern, return_value);
        if (type == IS_OBJECT) {
            FETCH_PHP_OBJECT_VAR_OTHER(Vector2, x_intern, x);
            if (zend_string_equals(x_intern->std.ce->name, PhpVector2_entry->name)) {
                new_intern->container = container->subtract(x_intern->container);
            } else {
                RETURN_NULL();
            }
        } else {
            new_intern->container = container->subtract(type == IS_DOUBLE ? Z_DVAL(*x) : Z_LVAL(*x), y);
        }

        UPDATE_CLASS_PROPERTY_DOUBLE_OTHER(PhpVector2_entry, return_value, "x", new_intern->container->x);
        UPDATE_CLASS_PROPERTY_DOUBLE_OTHER(PhpVector2_entry, return_value, "y", new_intern->container->y);
    }
}

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO(arginfo_Vector2_ceil, pocketmine\\math\\Vector2, 0)
ZEND_END_ARG_INFO()

PHP_CLASS_METHOD(PhpVector2, ceil, ZEND_ACC_PUBLIC) {
    zend_parse_parameters_none_throw();

    FETCH_PHP_OBJECT_CONTAINER_VAR(Vector2, container);

    object_init_ex(return_value, PhpVector2_entry);
    FETCH_PHP_OBJECT_VAR_OTHER(Vector2, new_intern, return_value);

    new_intern->container = container->ceil();

    UPDATE_CLASS_PROPERTY_DOUBLE_OTHER(PhpVector2_entry, return_value, "x", new_intern->container->x);
    UPDATE_CLASS_PROPERTY_DOUBLE_OTHER(PhpVector2_entry, return_value, "y", new_intern->container->y);
}

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO(arginfo_Vector2_floor, pocketmine\\math\\Vector2, 0)
ZEND_END_ARG_INFO()

PHP_CLASS_METHOD(PhpVector2, floor, ZEND_ACC_PUBLIC) {
    zend_parse_parameters_none_throw();

    FETCH_PHP_OBJECT_CONTAINER_VAR(Vector2, container);

    object_init_ex(return_value, PhpVector2_entry);
    FETCH_PHP_OBJECT_VAR_OTHER(Vector2, new_intern, return_value);

    new_intern->container = container->floor();

    UPDATE_CLASS_PROPERTY_DOUBLE_OTHER(PhpVector2_entry, return_value, "x", new_intern->container->x);
    UPDATE_CLASS_PROPERTY_DOUBLE_OTHER(PhpVector2_entry, return_value, "y", new_intern->container->y);
}

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO(arginfo_Vector2_round, pocketmine\\math\\Vector2, 0)
ZEND_END_ARG_INFO()

PHP_CLASS_METHOD(PhpVector2, round, ZEND_ACC_PUBLIC) {
    zend_parse_parameters_none_throw();

    FETCH_PHP_OBJECT_CONTAINER_VAR(Vector2, container);

    object_init_ex(return_value, PhpVector2_entry);
    FETCH_PHP_OBJECT_VAR_OTHER(Vector2, new_intern, return_value);

    new_intern->container = container->round();

    UPDATE_CLASS_PROPERTY_DOUBLE_OTHER(PhpVector2_entry, return_value, "x", new_intern->container->x);
    UPDATE_CLASS_PROPERTY_DOUBLE_OTHER(PhpVector2_entry, return_value, "y", new_intern->container->y);
}

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO(arginfo_Vector2_abs, pocketmine\\math\\Vector2, 0)
ZEND_END_ARG_INFO()

PHP_CLASS_METHOD(PhpVector2, abs, ZEND_ACC_PUBLIC) {
    zend_parse_parameters_none_throw();

    FETCH_PHP_OBJECT_CONTAINER_VAR(Vector2, container);

    object_init_ex(return_value, PhpVector2_entry);
    FETCH_PHP_OBJECT_VAR_OTHER(Vector2, new_intern, return_value);

    new_intern->container = container->abs();

    UPDATE_CLASS_PROPERTY_DOUBLE_OTHER(PhpVector2_entry, return_value, "x", new_intern->container->x);
    UPDATE_CLASS_PROPERTY_DOUBLE_OTHER(PhpVector2_entry, return_value, "y", new_intern->container->y);
}

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_Vector2_multiply, 0, 1, pocketmine\\math\\Vector2, 0)
    ZEND_ARG_TYPE_INFO(0, number, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

PHP_CLASS_METHOD(PhpVector2, multiply, ZEND_ACC_PUBLIC) {
    double number = NULL;

    ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 1, 1)
        Z_PARAM_DOUBLE(number)
    ZEND_PARSE_PARAMETERS_END();

    FETCH_PHP_OBJECT_CONTAINER_VAR(Vector2, container);

    object_init_ex(return_value, PhpVector2_entry);
    FETCH_PHP_OBJECT_VAR_OTHER(Vector2, new_intern, return_value);

    new_intern->container = container->multiply(number);

    UPDATE_CLASS_PROPERTY_DOUBLE_OTHER(PhpVector2_entry, return_value, "x", new_intern->container->x);
    UPDATE_CLASS_PROPERTY_DOUBLE_OTHER(PhpVector2_entry, return_value, "y", new_intern->container->y);
}

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_Vector2_divide, 0, 1, pocketmine\\math\\Vector2, 0)
    ZEND_ARG_TYPE_INFO(0, number, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

PHP_CLASS_METHOD(PhpVector2, divide, ZEND_ACC_PUBLIC) {
    double number = NULL;

    ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 1, 1)
            Z_PARAM_DOUBLE(number)
    ZEND_PARSE_PARAMETERS_END();

    FETCH_PHP_OBJECT_CONTAINER_VAR(Vector2, container);

    object_init_ex(return_value, PhpVector2_entry);
    FETCH_PHP_OBJECT_VAR_OTHER(Vector2, new_intern, return_value);

    new_intern->container = container->divide(number);

    UPDATE_CLASS_PROPERTY_DOUBLE_OTHER(PhpVector2_entry, return_value, "x", new_intern->container->x);
    UPDATE_CLASS_PROPERTY_DOUBLE_OTHER(PhpVector2_entry, return_value, "y", new_intern->container->y);
}

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_Vector2_distance, 0, 1, IS_DOUBLE, 0)
    ZEND_ARG_INFO(0, x)
    ZEND_ARG_TYPE_INFO(0, y, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

PHP_CLASS_METHOD(PhpVector2, distance, ZEND_ACC_PUBLIC) {
    zval *x = NULL;
    double y = 0;

    ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 1, 2)
        Z_PARAM_ZVAL(x)
        Z_PARAM_OPTIONAL
        Z_PARAM_DOUBLE(y)
    ZEND_PARSE_PARAMETERS_END();

    FETCH_PHP_OBJECT_CONTAINER_VAR(Vector2, container);

    zend_type type = Z_TYPE_P(x);
    if (type == IS_OBJECT or type == IS_LONG or type == IS_DOUBLE) {
        if (type == IS_OBJECT) {
            FETCH_PHP_OBJECT_VAR_OTHER(Vector2, x_intern, x);
            if (zend_string_equals(x_intern->std.ce->name, PhpVector2_entry->name)) {
                RETURN_DOUBLE(container->distance(x_intern->container));
            } else {
                RETURN_NULL();
            }
        } else {
            RETURN_DOUBLE(container->distance(type == IS_DOUBLE ? Z_DVAL(*x) : Z_LVAL(*x), y));
        }
    }
}

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_Vector2_distanceSquared, 0, 1, IS_DOUBLE, 0)
    ZEND_ARG_INFO(0, x)
    ZEND_ARG_TYPE_INFO(0, y, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

PHP_CLASS_METHOD(PhpVector2, distanceSquared, ZEND_ACC_PUBLIC) {
    zval *x = NULL;
    double y = 0;

    ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 1, 2)
        Z_PARAM_ZVAL(x)
        Z_PARAM_OPTIONAL
        Z_PARAM_DOUBLE(y)
    ZEND_PARSE_PARAMETERS_END();

    FETCH_PHP_OBJECT_CONTAINER_VAR(Vector2, container);

    zend_type type = Z_TYPE_P(x);
    if (type == IS_OBJECT or type == IS_LONG or type == IS_DOUBLE) {
        if (type == IS_OBJECT) {
            FETCH_PHP_OBJECT_VAR_OTHER(Vector2, x_intern, x);
            if (zend_string_equals(x_intern->std.ce->name, PhpVector2_entry->name)) {
                RETURN_DOUBLE(container->distanceSquared(x_intern->container));
            } else {
                RETURN_NULL();
            }
        } else {
            RETURN_DOUBLE(container->distanceSquared(type == IS_DOUBLE ? Z_DVAL(*x) : Z_LVAL(*x), y));
        }
    }
}

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO(arginfo_Vector2_length, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

PHP_CLASS_METHOD(PhpVector2, length, ZEND_ACC_PUBLIC) {
    zend_parse_parameters_none_throw();

    FETCH_PHP_OBJECT_CONTAINER_VAR(Vector2, container);

    RETURN_DOUBLE(container->length());
}

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO(arginfo_Vector2_lengthSquared, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

PHP_CLASS_METHOD(PhpVector2, lengthSquared, ZEND_ACC_PUBLIC) {
    zend_parse_parameters_none_throw();

    FETCH_PHP_OBJECT_CONTAINER_VAR(Vector2, container);

    RETURN_DOUBLE(container->lengthSquared());
}

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO(arginfo_Vector2_normalize, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

PHP_CLASS_METHOD(PhpVector2, normalize, ZEND_ACC_PUBLIC) {
    zend_parse_parameters_none_throw();

    FETCH_PHP_OBJECT_CONTAINER_VAR(Vector2, container);

    object_init_ex(return_value, PhpVector2_entry);
    FETCH_PHP_OBJECT_VAR_OTHER(Vector2, new_intern, return_value);

    new_intern->container = container->normalize();
}

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO(arginfo_Vector2_dot, IS_DOUBLE, 0)
    ZEND_ARG_OBJ_INFO(0, v, pocketmine\\math\\Vector2, 0)
ZEND_END_ARG_INFO()

PHP_CLASS_METHOD(PhpVector2, dot, ZEND_ACC_PUBLIC) {
    zval *v;

    ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 1, 2)
        Z_PARAM_OBJECT(v)
    ZEND_PARSE_PARAMETERS_END();

    FETCH_PHP_OBJECT_CONTAINER_VAR(Vector2, container);
    FETCH_PHP_OBJECT_CONTAINER_VAR_OTHER(Vector2, v_container, v);

    RETURN_DOUBLE(container->dot(v_container));
}

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO(arginfo_Vector2___toString, IS_STRING, 0)
ZEND_END_ARG_INFO()

PHP_CLASS_METHOD(PhpVector2, __toString, ZEND_ACC_PUBLIC) {
    zend_parse_parameters_none_throw();

    FETCH_PHP_OBJECT_CONTAINER_VAR(Vector2, container);

    RETURN_STRING(std::string("Vector2(x=" + std::to_string(container->x) + ",y=" + std::to_string(container->y) + ")").c_str());
}

void register_vector2_class() {
    REGISTER_FUNCTION_ENTRY_START()
        REGISTER_FUNCTION_ENTRY(PhpVector2, __construct,     arginfo_Vector2___construct)
        REGISTER_FUNCTION_ENTRY(PhpVector2, getX,            arginfo_Vector2_getX)
        REGISTER_FUNCTION_ENTRY(PhpVector2, getY,            arginfo_Vector2_getY)
        REGISTER_FUNCTION_ENTRY(PhpVector2, getFloorX,       arginfo_Vector2_getFloorX)
        REGISTER_FUNCTION_ENTRY(PhpVector2, getFloorY,       arginfo_Vector2_getFloorY)
        REGISTER_FUNCTION_ENTRY(PhpVector2, add,             arginfo_Vector2_add)
        REGISTER_FUNCTION_ENTRY(PhpVector2, subtract,        arginfo_Vector2_subtract)
        REGISTER_FUNCTION_ENTRY(PhpVector2, ceil,            arginfo_Vector2_ceil)
        REGISTER_FUNCTION_ENTRY(PhpVector2, floor,           arginfo_Vector2_floor)
        REGISTER_FUNCTION_ENTRY(PhpVector2, round,           arginfo_Vector2_round)
        REGISTER_FUNCTION_ENTRY(PhpVector2, abs,             arginfo_Vector2_abs)
        REGISTER_FUNCTION_ENTRY(PhpVector2, multiply,        arginfo_Vector2_multiply)
        REGISTER_FUNCTION_ENTRY(PhpVector2, divide,          arginfo_Vector2_divide)
        REGISTER_FUNCTION_ENTRY(PhpVector2, distance,        arginfo_Vector2_distance)
        REGISTER_FUNCTION_ENTRY(PhpVector2, distanceSquared, arginfo_Vector2_distanceSquared)
        REGISTER_FUNCTION_ENTRY(PhpVector2, length,          arginfo_Vector2_length)
        REGISTER_FUNCTION_ENTRY(PhpVector2, lengthSquared,   arginfo_Vector2_lengthSquared)
        REGISTER_FUNCTION_ENTRY(PhpVector2, normalize,       arginfo_Vector2_normalize)
        REGISTER_FUNCTION_ENTRY(PhpVector2, dot,             arginfo_Vector2_dot)
        REGISTER_FUNCTION_ENTRY(PhpVector2, __toString,      arginfo_Vector2___toString)
    REGISTER_FUNCTION_ENTRY_END();

    REGISTER_CLASS_WITH_HANDLERS_SET_ENTRY(Vector2, "pocketmine\\math\\Vector2", PhpVector2, php_PhpVector2_handlers);

    REGISTER_CLASS_PROPERTY_DOUBLE(PhpVector2_entry, "x", ZEND_ACC_PUBLIC);
    REGISTER_CLASS_PROPERTY_DOUBLE(PhpVector2_entry, "y", ZEND_ACC_PUBLIC);
}