//
// Created by Jack Noordhuis on 1/11/18.
//

#ifndef EXT_POCKETMINE_MATH_PHP_POCKETMINE_MATH_H
#define EXT_POCKETMINE_MATH_PHP_POCKETMINE_MATH_H

#include "php.h"

extern zend_module_entry pocketmine_math_module_entry;
#define phpext_pocketmine_math_ptr &pocketmine_math_module_entry

#define PHP_POCKETMINE_MATH_VERSION "0.1.0"

#ifdef ZTS
#include "TSRM.h"
#endif

#if defined(ZTS) && defined(COMPILE_DL_POCKETMINE_MATH)
ZEND_TSRMLS_CACHE_EXTERN()
#endif

#endif //EXT_POCKETMINE_MATH_PHP_POCKETMINE_MATH_H
