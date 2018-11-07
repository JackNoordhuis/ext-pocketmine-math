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

// Defines so we can use our macros in ZendUtil.h.
#define CLASS_TYPE Vector2
#define CLASS_NAME M_CONC(Php, CLASS_TYPE)
#define ARG_INFO_PREFIX M_CONC(arginfo_, M_CONC(CLASS_TYPE, _))


/* PHP-Land Vector2 class */

PHP_CLASS_ENTRY_EX();

ZEND_BEGIN_ARG_INFO_EX(ARG_INFO_NAME(__construct), 0, 0, 0)
    ZEND_ARG_TYPE_INFO(0, x, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(0, y, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

PHP_CLASS_METHOD(__construct, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR) {
    double x = 0;
    double y = 0;

    ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 0, 2)
        Z_PARAM_OPTIONAL
        Z_PARAM_DOUBLE(x)
        Z_PARAM_OPTIONAL
        Z_PARAM_DOUBLE(y)
    ZEND_PARSE_PARAMETERS_END();

    auto vector = new Vector2(x, y);

    UPDATE_CLASS_PROPERTY_DOUBLE("x", x);
    UPDATE_CLASS_PROPERTY_DOUBLE("y", y);

    SET_PHP_OBJECT_CONTAINER(vector);
}

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO(arginfo_Vector2_getX, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

PHP_CLASS_METHOD(getX, ZEND_ACC_PUBLIC) {
    zend_parse_parameters_none_throw();

    RETURN_DOUBLE(FETCH_PHP_OBJECT_CONTAINER()->getX());
}

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO(arginfo_Vector2_getY, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

PHP_CLASS_METHOD(getY, ZEND_ACC_PUBLIC) {
    zend_parse_parameters_none_throw();

    RETURN_DOUBLE(FETCH_PHP_OBJECT_CONTAINER()->getY());
}

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO(arginfo_Vector2_getFloorX, IS_LONG, 0)
ZEND_END_ARG_INFO()

PHP_CLASS_METHOD(getFloorX, ZEND_ACC_PUBLIC) {
    zend_parse_parameters_none_throw();

    RETURN_LONG(FETCH_PHP_OBJECT_CONTAINER()->getFloorX());
}

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO(arginfo_Vector2_getFloorY, IS_LONG, 0)
ZEND_END_ARG_INFO()

PHP_CLASS_METHOD(getFloorY, ZEND_ACC_PUBLIC) {
    zend_parse_parameters_none_throw();

    RETURN_LONG(FETCH_PHP_OBJECT_CONTAINER()->getFloorY());
}

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_Vector2_add, 0, 1, pocketmine\\math\\Vector2, 0)
    ZEND_ARG_INFO(0, x)
    ZEND_ARG_TYPE_INFO(0, y, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

PHP_CLASS_METHOD(add, ZEND_ACC_PUBLIC) {
    zval *x = nullptr;
    double y = 0;

    ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 1, 2)
        Z_PARAM_ZVAL(x)
        Z_PARAM_OPTIONAL
        Z_PARAM_DOUBLE(y)
    ZEND_PARSE_PARAMETERS_END();

    FETCH_PHP_OBJECT_CONTAINER_VAR(container);

    zend_type type = Z_TYPE_P(x);
    if (type == IS_OBJECT or type == IS_LONG or type == IS_DOUBLE) {
        object_init_ex(return_value, PhpVector2_entry);
        FETCH_PHP_OBJECT_VAR_OTHER(new_intern, return_value);
        if (type == IS_OBJECT) {
            FETCH_PHP_OBJECT_VAR_OTHER(x_intern, x);
            if (zend_string_equals(x_intern->std.ce->name, PhpVector2_entry->name)) {
                new_intern->container = container->add(x_intern->container);
            } else {
                RETURN_NULL();
            }
        } else {
            new_intern->container = container->add(type == IS_DOUBLE ? Z_DVAL(*x) : Z_LVAL(*x), y);
        }

        UPDATE_CLASS_PROPERTY_DOUBLE_OTHER(return_value, "x", new_intern->container->x);
        UPDATE_CLASS_PROPERTY_DOUBLE_OTHER(return_value, "y", new_intern->container->y);
    }
}

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_Vector2_subtract, 0, 1, pocketmine\\math\\Vector2, 0)
    ZEND_ARG_INFO(0, x)
    ZEND_ARG_TYPE_INFO(0, y, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

PHP_CLASS_METHOD(subtract, ZEND_ACC_PUBLIC) {
    zval *x = nullptr;
    double y = 0;

    ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 1, 2)
        Z_PARAM_ZVAL(x)
        Z_PARAM_OPTIONAL
        Z_PARAM_DOUBLE(y)
    ZEND_PARSE_PARAMETERS_END();

    FETCH_PHP_OBJECT_CONTAINER_VAR(container);

    zend_type type = Z_TYPE_P(x);
    if (type == IS_OBJECT or type == IS_LONG or type == IS_DOUBLE) {
        object_init_ex(return_value, PhpVector2_entry);
        FETCH_PHP_OBJECT_VAR_OTHER(new_intern, return_value);
        if (type == IS_OBJECT) {
            FETCH_PHP_OBJECT_VAR_OTHER(x_intern, x);
            if (zend_string_equals(x_intern->std.ce->name, PhpVector2_entry->name)) {
                new_intern->container = container->subtract(x_intern->container);
            } else {
                RETURN_NULL();
            }
        } else {
            new_intern->container = container->subtract(type == IS_DOUBLE ? Z_DVAL(*x) : Z_LVAL(*x), y);
        }

        UPDATE_CLASS_PROPERTY_DOUBLE_OTHER(return_value, "x", new_intern->container->x);
        UPDATE_CLASS_PROPERTY_DOUBLE_OTHER(return_value, "y", new_intern->container->y);
    }
}

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO(arginfo_Vector2_ceil, pocketmine\\math\\Vector2, 0)
ZEND_END_ARG_INFO()

PHP_CLASS_METHOD(ceil, ZEND_ACC_PUBLIC) {
    zend_parse_parameters_none_throw();

    FETCH_PHP_OBJECT_CONTAINER_VAR(container);

    object_init_ex(return_value, PhpVector2_entry);
    FETCH_PHP_OBJECT_VAR_OTHER(new_intern, return_value);

    new_intern->container = container->ceil();

    UPDATE_CLASS_PROPERTY_DOUBLE_OTHER(return_value, "x", new_intern->container->x);
    UPDATE_CLASS_PROPERTY_DOUBLE_OTHER(return_value, "y", new_intern->container->y);
}

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO(arginfo_Vector2_floor, pocketmine\\math\\Vector2, 0)
ZEND_END_ARG_INFO()

PHP_CLASS_METHOD(floor, ZEND_ACC_PUBLIC) {
    zend_parse_parameters_none_throw();

    FETCH_PHP_OBJECT_CONTAINER_VAR(container);

    object_init_ex(return_value, PhpVector2_entry);
    FETCH_PHP_OBJECT_VAR_OTHER(new_intern, return_value);

    new_intern->container = container->floor();

    UPDATE_CLASS_PROPERTY_DOUBLE_OTHER(return_value, "x", new_intern->container->x);
    UPDATE_CLASS_PROPERTY_DOUBLE_OTHER(return_value, "y", new_intern->container->y);
}

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO(arginfo_Vector2_round, pocketmine\\math\\Vector2, 0)
ZEND_END_ARG_INFO()

PHP_CLASS_METHOD(round, ZEND_ACC_PUBLIC) {
    zend_parse_parameters_none_throw();

    FETCH_PHP_OBJECT_CONTAINER_VAR(container);

    object_init_ex(return_value, PhpVector2_entry);
    FETCH_PHP_OBJECT_VAR_OTHER(new_intern, return_value);

    new_intern->container = container->round();

    UPDATE_CLASS_PROPERTY_DOUBLE_OTHER(return_value, "x", new_intern->container->x);
    UPDATE_CLASS_PROPERTY_DOUBLE_OTHER(return_value, "y", new_intern->container->y);
}

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO(arginfo_Vector2_abs, pocketmine\\math\\Vector2, 0)
ZEND_END_ARG_INFO()

PHP_CLASS_METHOD(abs, ZEND_ACC_PUBLIC) {
    zend_parse_parameters_none_throw();

    FETCH_PHP_OBJECT_CONTAINER_VAR(container);

    object_init_ex(return_value, PhpVector2_entry);
    FETCH_PHP_OBJECT_VAR_OTHER(new_intern, return_value);

    new_intern->container = container->abs();

    UPDATE_CLASS_PROPERTY_DOUBLE_OTHER(return_value, "x", new_intern->container->x);
    UPDATE_CLASS_PROPERTY_DOUBLE_OTHER(return_value, "y", new_intern->container->y);
}

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_Vector2_multiply, 0, 1, pocketmine\\math\\Vector2, 0)
    ZEND_ARG_TYPE_INFO(0, number, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

PHP_CLASS_METHOD(multiply, ZEND_ACC_PUBLIC) {
    double number = 0;

    ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 1, 1)
        Z_PARAM_DOUBLE(number)
    ZEND_PARSE_PARAMETERS_END();

    FETCH_PHP_OBJECT_CONTAINER_VAR(container);

    object_init_ex(return_value, PhpVector2_entry);
    FETCH_PHP_OBJECT_VAR_OTHER(new_intern, return_value);

    new_intern->container = container->multiply(number);

    UPDATE_CLASS_PROPERTY_DOUBLE_OTHER(return_value, "x", new_intern->container->x);
    UPDATE_CLASS_PROPERTY_DOUBLE_OTHER(return_value, "y", new_intern->container->y);
}

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_Vector2_divide, 0, 1, pocketmine\\math\\Vector2, 0)
    ZEND_ARG_TYPE_INFO(0, number, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

PHP_CLASS_METHOD(divide, ZEND_ACC_PUBLIC) {
    double number = 0;

    ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 1, 1)
            Z_PARAM_DOUBLE(number)
    ZEND_PARSE_PARAMETERS_END();

    FETCH_PHP_OBJECT_CONTAINER_VAR(container);

    object_init_ex(return_value, PhpVector2_entry);
    FETCH_PHP_OBJECT_VAR_OTHER(new_intern, return_value);

    new_intern->container = container->divide(number);

    UPDATE_CLASS_PROPERTY_DOUBLE_OTHER(return_value, "x", new_intern->container->x);
    UPDATE_CLASS_PROPERTY_DOUBLE_OTHER(return_value, "y", new_intern->container->y);
}

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_Vector2_distance, 0, 1, IS_DOUBLE, 0)
    ZEND_ARG_INFO(0, x)
    ZEND_ARG_TYPE_INFO(0, y, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

PHP_CLASS_METHOD(distance, ZEND_ACC_PUBLIC) {
    zval *x = nullptr;
    double y = 0;

    ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 1, 2)
        Z_PARAM_ZVAL(x)
        Z_PARAM_OPTIONAL
        Z_PARAM_DOUBLE(y)
    ZEND_PARSE_PARAMETERS_END();

    FETCH_PHP_OBJECT_CONTAINER_VAR(container);

    zend_type type = Z_TYPE_P(x);
    if (type == IS_OBJECT or type == IS_LONG or type == IS_DOUBLE) {
        if (type == IS_OBJECT) {
            FETCH_PHP_OBJECT_VAR_OTHER(x_intern, x);
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

PHP_CLASS_METHOD(distanceSquared, ZEND_ACC_PUBLIC) {
    zval *x = nullptr;
    double y = 0;

    ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 1, 2)
        Z_PARAM_ZVAL(x)
        Z_PARAM_OPTIONAL
        Z_PARAM_DOUBLE(y)
    ZEND_PARSE_PARAMETERS_END();

    FETCH_PHP_OBJECT_CONTAINER_VAR(container);

    zend_type type = Z_TYPE_P(x);
    if (type == IS_OBJECT or type == IS_LONG or type == IS_DOUBLE) {
        if (type == IS_OBJECT) {
            FETCH_PHP_OBJECT_VAR_OTHER(x_intern, x);
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

PHP_CLASS_METHOD(length, ZEND_ACC_PUBLIC) {
    zend_parse_parameters_none_throw();

    FETCH_PHP_OBJECT_CONTAINER_VAR(container);

    RETURN_DOUBLE(container->length());
}

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO(arginfo_Vector2_lengthSquared, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

PHP_CLASS_METHOD(lengthSquared, ZEND_ACC_PUBLIC) {
    zend_parse_parameters_none_throw();

    FETCH_PHP_OBJECT_CONTAINER_VAR(container);

    RETURN_DOUBLE(container->lengthSquared());
}

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_Vector2_normalize, 0, 0, pocketmine\\math\\Vector2, 0)
ZEND_END_ARG_INFO()

PHP_CLASS_METHOD(normalize, ZEND_ACC_PUBLIC) {
    zend_parse_parameters_none_throw();

    FETCH_PHP_OBJECT_CONTAINER_VAR(container);

    object_init_ex(return_value, PhpVector2_entry);
    FETCH_PHP_OBJECT_VAR_OTHER(new_intern, return_value);

    new_intern->container = container->normalize();
}

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO(arginfo_Vector2_dot, IS_DOUBLE, 0)
    ZEND_ARG_OBJ_INFO(0, v, pocketmine\\math\\Vector2, 0)
ZEND_END_ARG_INFO()

PHP_CLASS_METHOD(dot, ZEND_ACC_PUBLIC) {
    zval *v;

    ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 1, 2)
        Z_PARAM_OBJECT(v)
    ZEND_PARSE_PARAMETERS_END();

    FETCH_PHP_OBJECT_CONTAINER_VAR(container);
    FETCH_PHP_OBJECT_CONTAINER_VAR_OTHER(v_container, v);

    RETURN_DOUBLE(container->dot(v_container));
}

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO(arginfo_Vector2___toString, IS_STRING, 0)
ZEND_END_ARG_INFO()

PHP_CLASS_METHOD(__toString, ZEND_ACC_PUBLIC) {
    zend_parse_parameters_none_throw();

    FETCH_PHP_OBJECT_CONTAINER_VAR(container);

    RETURN_STRING(std::string("Vector2(x=" + std::to_string(container->x) + ",y=" + std::to_string(container->y) + ")").c_str());
}

void register_vector2_class() {
    REGISTER_FUNCTION_ENTRY_START()
        REGISTER_FUNCTION_ENTRY(__construct)
        REGISTER_FUNCTION_ENTRY(getX)
        REGISTER_FUNCTION_ENTRY(getY)
        REGISTER_FUNCTION_ENTRY(getFloorX)
        REGISTER_FUNCTION_ENTRY(getFloorY)
        REGISTER_FUNCTION_ENTRY(add)
        REGISTER_FUNCTION_ENTRY(subtract)
        REGISTER_FUNCTION_ENTRY(ceil)
        REGISTER_FUNCTION_ENTRY(floor)
        REGISTER_FUNCTION_ENTRY(round)
        REGISTER_FUNCTION_ENTRY(abs)
        REGISTER_FUNCTION_ENTRY(multiply)
        REGISTER_FUNCTION_ENTRY(divide)
        REGISTER_FUNCTION_ENTRY(distance)
        REGISTER_FUNCTION_ENTRY(distanceSquared)
        REGISTER_FUNCTION_ENTRY(length)
        REGISTER_FUNCTION_ENTRY(lengthSquared)
        REGISTER_FUNCTION_ENTRY(normalize)
        REGISTER_FUNCTION_ENTRY(dot)
        REGISTER_FUNCTION_ENTRY(__toString)
    REGISTER_FUNCTION_ENTRY_END();

    REGISTER_CLASS_WITH_HANDLERS_SET_ENTRY("pocketmine\\math\\Vector2");

    REGISTER_CLASS_PROPERTY_DOUBLE("x", ZEND_ACC_PUBLIC);
    REGISTER_CLASS_PROPERTY_DOUBLE("y", ZEND_ACC_PUBLIC);
}

// Undefine so we can use the macros for other classes.
#undef CLASS_TYPE
#undef CLASS_NAME
#undef ARG_INFO_PREFIX