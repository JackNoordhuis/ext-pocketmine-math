//
// Created by Jack Noordhuis on 1/11/18.
//

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "src/PhpBearing.h"
#include "src/PhpFacing.h"
#include "src/PhpVector2.h"

extern "C" {
#include "php.h"
#include "ext/standard/info.h"
#include "php_pocketmine_math.h" // this one has to be C always, so the engine can understand it
}

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(pocketmine_math)
{
    // register php things
    register_bearing_class();
    register_facing_class();
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


/* {{{ pocketmine_math_module_entry
 */
zend_module_entry pocketmine_math_module_entry = {
        STANDARD_MODULE_HEADER,
        "pocketmine_math",				    /* Extension name */
        NULL,				                /* zend_function_entry */
        PHP_MINIT(pocketmine_math),		    /* PHP_MINIT - Module initialization */
        NULL,	                            /* PHP_MSHUTDOWN - Module shutdown */
        NULL,				                /* PHP_RINIT - Request initialization */
        NULL,								/* PHP_RSHUTDOWN - Request shutdown */
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