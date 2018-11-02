//
// Created by Jack Noordhuis on 1/11/18.
//

#ifndef EXT_POCKETMINE_MATH_ZENDUTIL_H
#define EXT_POCKETMINE_MATH_ZENDUTIL_H

extern "C" {
#include "php.h"
}

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

#define REGISTER_CLASS(type, name, functions) \
    register_zend_class<type>(name, functions)

#define REGISTER_CLASS_SET_ENTRY(type, name, functions, entry) \
    entry = register_zend_class<type>(name, functions)

#define REGISTER_CLASS_EX(type, handlers, name, functions) \
    register_zend_class<type>(handlers, name, functions)

#define REGISTER_CLASS_SET_ENTRY_EX(type, handlers, name, functions, entry) \
    entry = register_zend_class<type>(handlers, name, functions)

#define REGISTER_CLASS_CONST_LONG(class_entry, name, value) \
	zend_declare_class_constant_long(class_entry, name, sizeof(name)-1, (zend_long)value)

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
