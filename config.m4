dnl $Id$
dnl config.m4 for extension pocketmine_math

PHP_ARG_ENABLE(pocketmine_math, whether to enable pocketmine_math support,
[  --enable-pocketmine-math           Enable PocketMine Math extension])

if test "$PHP_POCKETMINE_MATH" != "no"; then
  PHP_REQUIRE_CXX()

  dnl apparently PHP_REQUIRE_CXX() isn't good enough if we're compiling as a shared library
  PHP_ADD_LIBRARY(stdc++, 1, POCKETMINE_MATH_SHARED_LIBADD)
  PHP_SUBST(SOCKET_SERVER_SHARED_LIBADD)

  PHP_NEW_EXTENSION(pocketmine_math, pocketmine_math.cpp lib/AxisAlignedBB.cpp lib/Bearing.cpp lib/Facing.cpp src/PhpBearing.cpp src/PhpFacing.cpp, $ext_shared,, -DZEND_ENABLE_STATIC_TSRMLS_CACHE=1 -std=c++11)
  PHP_ADD_BUILD_DIR($ext_builddir/src, 1)
  PHP_ADD_BUILD_DIR($ext_builddir/lib, 1)
  PHP_ADD_INCLUDE($ext_builddir)
fi