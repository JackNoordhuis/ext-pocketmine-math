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
 * @return Pointer to the zend class entry.
 */
template<class T>
static inline zend_class_entry *register_zend_class(zend_object_handlers *handlers, const char *name, zend_function_entry *functions) {
    memcpy(handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    handlers->offset = XtOffsetOf(class_obj<T>, std);
    handlers->free_obj = deallocate_zend_obj<T>;

    zend_class_entry *ce = register_zend_class<T>(name, functions);
    ce->create_object = [handlers](zend_class_entry *class_type) { return allocate_zend_obj<T>(class_type, handlers); };
    return ce;
}



 /*******************************************************************
 *                                                                  *
 *     Macros for simplifying the extension development process.    *
 *                                                                  *
 *******************************************************************/

/*
 * Macros for the starting definition of a class. Defines class entry pointer and
 * extended macro provides handler list for constructing php land objects.
 */
#define PHP_CLASS_ENTRY(classname) \
    zend_class_entry *classname##_entry

#define PHP_CLASS_ENTRY_EX(classname) \
    PHP_CLASS_ENTRY(classname) \
    zend_object_handlers *classname##_handlers


/*
 * Macro to perform PHP_METHOD functionality whilst keeping method flags in the same
 * area of code as method definition.
 */
#define PHP_CLASS_METHOD(classname, name, flags) \
    php_class_method_definition php_##classname##_##name##_method = { flags }; \
    PHP_METHOD(classname, name)


/*
 * Macros to provide consistent functionality for declaring php land functions.
 * Using macros to define the zend_function_entry array and reducing duplicate arguments.
 */
#define REGISTER_FUNCTION_ENTRY_START_EX(name) \
    zend_function_entry php_##name[] = {

#define REGISTER_FUNCTION_ENTRY_START() \
    zend_function_entry php_methods[] = {

#define REGISTER_FUNCTION_ENTRY(classname, name, arg_info) \
    PHP_ME(classname, name, arg_info, php_##classname##_##name##_method.flags)

#define REGISTER_FUNCTION_ENTRY_END() \
    PHP_FE_END \
    }


/*
 * Macros to provide quick and easy access to registering a php land class.
 */
#define REGISTER_CLASS_EX(type, name, classname, handlers) \
    classname##_entry = register_zend_class<type>(name, *#handlers)

#define REGISTER_CLASS_SET_ENTRY_EX(type, name, classname, method_handlers) \
    classname##_entry = register_zend_class<type>(name, php_##method_handlers)

#define REGISTER_CLASS_SET_ENTRY(type, name, classname) \
    REGISTER_CLASS_SET_ENTRY_EX(type, name, classname, methods)


/*
 * Helper macros for defining class constants.
 */

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

#endif //EXT_POCKETMINE_MATH_ZENDUTIL_H
