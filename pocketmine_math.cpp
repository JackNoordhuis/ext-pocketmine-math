//
// Created by Jack Noordhuis on 1/11/18.
//

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#ifdef POCKETMINE_MATH_DEBUG
#include <iostream>
#endif

#include "src/PhpBearing.h"
#include "src/PhpFacing.h"
#include "src/PhpMath.h"
#include "src/PhpVector2.h"

extern "C" {
#include <SAPI.h>
#include "ext/standard/info.h"
#include "php_pocketmine_math.h" // this one has to be C always, so the engine can understand it
}

typedef struct _pocketmine_math_supported_sapi_t {
    const char *name;
    size_t      nlen;
} pocketmine_math_supported_sapi_t;

const static pocketmine_math_supported_sapi_t debug_whitelist[] = {
        {ZEND_STRL("cli")},
        {ZEND_STRL("phpdbg")},
        {ZEND_STRL("homegear")},
        {NULL, 0}
};

static inline bool pocketmine_math_is_supported_sapi(char *name) {
#ifndef POCKETMINE_MATH_DEBUG
    return true;
#else
    const pocketmine_math_supported_sapi_t *sapi = debug_whitelist;
    size_t nlen = strlen(name);

    while (sapi->name) {
        if (nlen == sapi->nlen &&
            memcmp(sapi->name, name, nlen) == SUCCESS) {
            return true;
        }
        sapi++;
    }

    return false;
#endif
}

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(pocketmine_math)
{
#ifdef POCKETMINE_MATH_DEBUG
    if(!pocketmine_math_is_supported_sapi(sapi_module.name)) { // only allow debug mode to run in CLI environments
        zend_error(E_ERROR, "The %s SAPI is not supported by pocketmine_math in debug mode",
                   sapi_module.name);
        return FAILURE;
    }

    // wait for 'enter' key press before initializing module to allow debugging programs to attach to the process
    std::cout << '\n' << "Press enter key to continue...";
    while (std::getchar() != '\n'){}
#endif

    // register php things
    register_bearing_class();
    register_facing_class();
    register_math_class();
    register_vector2_class();

    return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(pocketmine_math)
{
    php_info_print_table_start();
    php_info_print_table_header(2, "pocketmine_math support", "enabled");
    php_info_print_table_end();

}
/* }}} */

/* {{{ PHP_MSHUTDOWN
 */
PHP_MSHUTDOWN_FUNCTION(pocketmine_math)
{
    return SUCCESS;
}
/* }}} */

/* {{{ pocketmine_math_module_entry
 */
zend_module_entry pocketmine_math_module_entry = {
        STANDARD_MODULE_HEADER,
        "pocketmine_math",				    /* Extension name */
        NULL,				                /* zend_function_entry */
        PHP_MINIT(pocketmine_math),		    /* PHP_MINIT - Module initialization */
        PHP_MSHUTDOWN(pocketmine_math),	    /* PHP_MSHUTDOWN - Module shutdown */
        NULL,				                /* PHP_RINIT - Request initialization */
        NULL,		                        /* PHP_RSHUTDOWN - Request shutdown */
        PHP_MINFO(pocketmine_math),		    /* PHP_MINFO - Module info */
        PHP_POCKETMINE_MATH_VERSION,		/* Version */
        STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_POCKETMINE_MATH
extern "C" {
#ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
#endif
ZEND_GET_MODULE(pocketmine_math)
}
#endif