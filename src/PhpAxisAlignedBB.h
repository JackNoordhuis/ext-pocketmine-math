//
// Created by Jack Noordhuis on 12/11/18.
//

#ifndef EXT_POCKETMINE_MATH_PHPAXISALIGNEDBB_H
#define EXT_POCKETMINE_MATH_PHPAXISALIGNEDBB_H

#include "ZendUtil.h"

// Defines so we can use our macros in ZendUtil.h.
#define CLASS_TYPE AxisAlignedBB

PHP_CLASS_METHOD(__construct);
PHP_CLASS_METHOD(setBounds);
PHP_CLASS_METHOD(setBB);
PHP_CLASS_METHOD(addCoord);
PHP_CLASS_METHOD(expand);
PHP_CLASS_METHOD(expandedCopy);
PHP_CLASS_METHOD(offset);
PHP_CLASS_METHOD(offsetCopy);
PHP_CLASS_METHOD(contract);
PHP_CLASS_METHOD(contractedCopy);
PHP_CLASS_METHOD(calculateXOffset);
PHP_CLASS_METHOD(calculateYOffset);
PHP_CLASS_METHOD(calculateZOffset);
PHP_CLASS_METHOD(intersectsWith);
PHP_CLASS_METHOD(isVectorInside);
PHP_CLASS_METHOD(getAverageEdgeLength);
PHP_CLASS_METHOD(isVectorInYZ);
PHP_CLASS_METHOD(isVectorInXZ);
PHP_CLASS_METHOD(isVectorInXY);
PHP_CLASS_METHOD(calculateIntercept);
PHP_CLASS_METHOD(__toString);

void register_axisalignedbb_class();

// Undefine so we can use the macros for other classes.
#undef CLASS_TYPE

#endif //EXT_POCKETMINE_MATH_PHPAXISALIGNEDBB_H
