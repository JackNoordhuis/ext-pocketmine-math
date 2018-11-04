//
// Created by Jack Noordhuis on 1/11/18.
//

#ifndef EXT_POCKETMINE_MATH_ZENDUTIL_H
#define EXT_POCKETMINE_MATH_ZENDUTIL_H

#include <vector>

extern "C" {
#include "php.h"
#include "php_pocketmine_math.h"
}

/**
 * A simple struct for keeping track of a zend classes flags.
 */
struct php_class_method_definition {
    uint32_t flags;
};

/**
 * A simple struct for keeping track of the encapsulated C++ and its zend object.
 *
 * @tparam T  The C++ class being encapsulated.
 */
template<class T>
struct class_obj {
    T *container;
    zend_object std;
};

/**
 * A helper function for retrieving a C++ object using a pointer to its zend object.
 *
 * @tparam class_name
 * @param obj
 * @return
 */
template<class T>
static inline class_obj<T> *fetch_from_zend_object(zend_object *obj) {
    return (class_obj<T> *)((char *)obj - XtOffsetOf(class_obj<T>, std));
}

/**
 * A helper function to allocate a zend objects memory.
 *
 * @tparam T          The C++ class being encapsulated.
 * @param class_type  A pointer to the zend class entry.
 * @param handlers    A pointer to the zend object handlers.
 *
 * @return A pointer to the new zend object.
 */
template<class T>
static inline zend_object *allocate_zend_obj(zend_class_entry *class_type, zend_object_handlers *handlers) {
    auto object = (class_obj<T> *)ecalloc(1, sizeof(class_obj<T>) + zend_object_properties_size(class_type));

    zend_object_std_init(&object->std, class_type);
    object_properties_init(&object->std, class_type);

    object->std.handlers = handlers;

    return &object->std;
}

/**
 * A helper function to deallocate a zend objects memory.
 *
 * @tparam T  The C++ class being encapsulated.
 * @param obj A pointer to the zend object being deallocated.
 */
template<class T>
static inline void deallocate_zend_obj(zend_object *obj) {
    auto object = fetch_from_zend_object<T>(obj);
    delete object->container;

    // call the standard free handler
    zend_object_std_dtor(&object->std);
}

/**
 * A helper function to register a class to the zend engine.
 *
 * @tparam T         The C++ class being encapsulated.
 * @param handlers   A pointer to the zend object handlers.
 * @param name       The name/namespace of the class.
 * @param functions  A pointer to the classes method definitions.
 *
 * @return Pointer to the zend class entry.
 */
template<class T>
static inline zend_class_entry *register_zend_class(const char *name, zend_function_entry *functions) {
    zend_class_entry ce;
    INIT_CLASS_ENTRY_EX(ce, name, strlen(name), functions);
    return zend_register_internal_class(&ce);
}

/**
 * A helper function to register a class to the zend engine.
 *
 * @tparam T         The C++ class being encapsulated.
 * @param handlers   A pointer to the zend object handlers.
 * @param name       The name/namespace of the class.
 * @param functions  A pointer to the classes method definitions.
 *
 * @param class_zend_allocation  A pointer to a function that allocates memory for the zend class.
 *
 * @return Pointer to the zend class entry.
 */
template<class T>
static inline zend_class_entry *register_zend_class(zend_object_handlers *handlers, const char *name, zend_function_entry *functions, zend_object *(*class_zend_allocation)(zend_class_entry *)) {
    memcpy(handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    handlers->offset = XtOffsetOf(class_obj<T>, std);
    handlers->free_obj = deallocate_zend_obj<T>;

    zend_class_entry *ce = register_zend_class<T>(name, functions);
    ce->create_object = class_zend_allocation;
    return ce;
}



 /*******************************************************************
 *                                                                  *
 *     Macros for simplifying the extension development process.    *
 *                                                                  *
 *******************************************************************/

// Macros for the starting definition of a class.

/*
 * Defines class entry pointer.
 */
#define PHP_CLASS_ENTRY(classname) \
    zend_class_entry *classname##_entry

/*
 * Defines class entry pointer and handler list for constructing php land objects.
 */
#define PHP_CLASS_ENTRY_EX(classname, type) \
    PHP_CLASS_ENTRY(classname); \
    zend_object_handlers php_##classname##_handlers; \
    static zend_object *allocate_##classname##_zend_obj(zend_class_entry *class_type) { \
        return allocate_zend_obj<type>(class_type, &php_##classname##_handlers); \
    }


// Macros for defining class methods

/*
 * Performs PHP_METHOD functionality whilst keeping method flags in the same
 * area of code as method definition.
 */
#define PHP_CLASS_METHOD(classname, name, flags) \
    php_class_method_definition php_##classname##_##name##_method = { flags }; \
    PHP_METHOD(classname, name)


// Macros to provide consistent functionality for declaring php land functions that reduce duplicate arguments.

/*
 * Start function entry definition and assign to supplied var name.
 */
#define REGISTER_FUNCTION_ENTRY_START_EX(name) \
    zend_function_entry php_##name[] = {

/*
 * Start function entry definition.
 */
#define REGISTER_FUNCTION_ENTRY_START() \
    zend_function_entry php_methods[] = {

/*
 * Add class function definition.
 */
#define REGISTER_FUNCTION_ENTRY(classname, name, arg_info) \
    PHP_ME(classname, name, arg_info, php_##classname##_##name##_method.flags)

/*
 * End function entry definition.
 */
#define REGISTER_FUNCTION_ENTRY_END() \
    PHP_FE_END \
    }


// Macros to provide quick and easy access to registering a php land class.

/*
 * Register a class to the zend engine with method definitions.
 */
#define REGISTER_CLASS_SET_ENTRY_EX(type, name, classname, method_handlers) \
    classname##_entry = register_zend_class<type>(name, php_##method_handlers)

/*
 * Register a class to the zend engine.
 */
#define REGISTER_CLASS_SET_ENTRY(type, name, classname) \
    classname##_entry = register_zend_class<type>(name, php_methods)

/*
 * Register a class to the zend engine with no methods.
 */
#define REGISTER_CLASS(type, name, classname) \
    REGISTER_FUNCTION_ENTRY_START() \
    REGISTER_FUNCTION_ENTRY_END(); \
    classname##_entry = REGISTER_CLASS_SET_ENTRY(type, name, classname)

/*
 * Register a class to the zend engine with method definitions and object handlers.
 */
#define REGISTER_CLASS_WITH_HANDLERS_SET_ENTRY_EX(type, name, classname, method_handlers, object_handlers) \
    classname##_entry = register_zend_class<type>(&object_handlers, name, php_##method_handlers, allocate_##classname##_zend_obj)

/*
 * Register a class to the zend engine with object handlers.
 */
#define REGISTER_CLASS_WITH_HANDLERS_SET_ENTRY(type, name, classname, object_handlers) \
    classname##_entry = register_zend_class<type>(&object_handlers, name, php_methods, allocate_##classname##_zend_obj)

/*
 * Register a class to the zend engine with object handlers and no methods.
 */
#define REGISTER_CLASS_WITH_HANDLERS(type, name, classname, handlers) \
    REGISTER_FUNCTION_ENTRY_START() \
    REGISTER_FUNCTION_ENTRY_END(); \
    REGISTER_CLASS_WITH_HANDLERS_SET_ENTRY(type, object_handlers, name)


//Helper macros for defining class constants.

#define REGISTER_CLASS_CONST_LONG(class_entry, name, value) \
	zend_declare_class_constant_long(class_entry, name, sizeof(name)-1, (zend_long)value)

/*
 * Defines a php land class constant array of longs from a C-style integer array.
 */
#define REGISTER_CLASS_CONST_LONG_ARRAY(class_entry, name, value) do { \
    HashTable *ht; \
    ALLOC_HASHTABLE(ht); \
    int value_len = sizeof(value)/sizeof(value[0]); \
    zend_hash_init(ht, value_len, NULL, NULL, 0); \
        for(int i = 0; i < value_len; ++i) { \
        zval val; \
        ZVAL_LONG(&val, value[i]); \
        zend_hash_index_update(ht, i, &val); \
    } \
    zval arr; \
    ZVAL_ARR(&arr, ht); \
    zend_declare_class_constant(class_entry, name, sizeof(name)-1, &arr); \
    } while (0)



// Helper macros for defining and updating class properties.

/*
 * Define a php class property with a default value.
 */
#define REGISTER_CLASS_PROPERTY_EX(class_entry, name, acc_flags, default_value) \
    zend_declare_property(class_entry, name, sizeof(name)-1, default_value, acc_flags)

/*
* Define a php class property.
*/
#define REGISTER_CLASS_PROPERTY(class_entry, name, acc_flags) \
    REGISTER_CLASS_PROPERTY_EX(class_entry, name, acc_flags, NULL)

/*
 * Define a php class property of type float with a default value.
 */
#define REGISTER_CLASS_PROPERTY_DOUBLE_EX(class_entry, name, acc_flags, default_value) \
    zend_declare_property_double(class_entry, name, sizeof(name)-1, default_value, acc_flags)

/*
 * Define a php class property of type float.
 */
#define REGISTER_CLASS_PROPERTY_DOUBLE(class_entry, name, acc_flags) \
    REGISTER_CLASS_PROPERTY_DOUBLE_EX(class_entry, name, acc_flags, NULL)

/*
 * Update a php class property.
 */
#define UPDATE_CLASS_PROPERTY_OTHER(class_entry, obj, name, new_value) \
    zend_update_property(class_entry, obj, name, sizeof(name)-1, new_value)

/*
 * Update a php class property on the current object.
 */
#define UPDATE_CLASS_PROPERTY(class_entry, name, new_value) \
    UPDATE_CLASS_PROPERTY_OTHER(class_entry, getThis(), name, new_value)

/*
 * Update a php class property of type float.
 */
#define UPDATE_CLASS_PROPERTY_DOUBLE_OTHER(class_entry, obj, name, new_value) \
    zend_update_property_double(class_entry, obj, name, sizeof(name)-1, new_value)

/*
* Update a php class property on the current object of type float.
*/
#define UPDATE_CLASS_PROPERTY_DOUBLE(class_entry, name, new_value) \
    UPDATE_CLASS_PROPERTY_DOUBLE_OTHER(class_entry, getThis(), name, new_value)


// Helper macros for dealing with C++ objects encapsulated in a class_obj struct.

/*
 * Retrieve a class_obj struct from a zval pointer.
 */
#define FETCH_PHP_OBJECT_OTHER(type, obj) \
    fetch_from_zend_object<type>(Z_OBJ_P(obj))

/*
* Retrieve a class_obj struct from the current class.
*/
#define FETCH_PHP_OBJECT(type) \
    FETCH_PHP_OBJECT_OTHER(type, getThis())

/*
 * Retrieve a class_obj struct from the current class and store in the variable var.
 */
#define FETCH_PHP_OBJECT_VAR(type, var) \
    auto var = FETCH_PHP_OBJECT(type)

/*
 * Retrieve a class_obj struct from a zval pointer and store in the variable var.
 */
#define FETCH_PHP_OBJECT_VAR_OTHER(type, var, obj_p) \
    auto var = FETCH_PHP_OBJECT_OTHER(type, obj_p)

/*
 * Retrieve a pointer to the C++ object from the current class.
 */
#define FETCH_PHP_OBJECT_CONTAINER(type) \
    fetch_from_zend_object<type>(Z_OBJ_P(getThis()))->container

/*
 * Retrieve a pointer to the C++ object from a zval pointer.
 */
#define FETCH_PHP_OBJECT_CONTAINER_OTHER(type, obj_p) \
    fetch_from_zend_object<type>(Z_OBJ_P(obj_p))->container

/*
 * Retrieve a pointer to the C++ object from a zval pointer and store in the variable var.
 */
#define FETCH_PHP_OBJECT_CONTAINER_VAR_OTHER(type, var, obj_p) \
    auto var = FETCH_PHP_OBJECT_CONTAINER_OTHER(type, obj_p)

/*
 * Retrieve a pointer to the C++ object from the current class and store in the variable var.
 */
#define FETCH_PHP_OBJECT_CONTAINER_VAR(type, var) \
    FETCH_PHP_OBJECT_CONTAINER_VAR_OTHER(type, var, getThis())

/*
 * Set the C++ object of a zval pointer.
 */
#define SET_PHP_OBJECT_CONTAINER_EX(type, value, obj) do { \
    FETCH_PHP_OBJECT_VAR_OTHER(type, temp_##type, obj); \
    temp_##type->container = value; \
    } while (0)

/*
 * Set the C++ object of the current object.
 */
#define SET_PHP_OBJECT_CONTAINER(type, value) \
    SET_PHP_OBJECT_CONTAINER_EX(type, value, getThis())

#endif //EXT_POCKETMINE_MATH_ZENDUTIL_H
