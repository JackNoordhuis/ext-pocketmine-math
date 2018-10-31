# dummy cmakelists.txt file for autocompletion features in clion
cmake_minimum_required(VERSION 3.12)
project(ext_pocketmine_math)

set(CMAKE_CXX_STANDARD 11)

file(GLOB_RECURSE SRC_LIST FOLLOW_SYMLINKS *.cpp)
file(GLOB_RECURSE HEAD_FILES FOLLOW_SYMLINKS *.h)

set(PHP_SOURCE /usr/local/Cellar/php/7.2.6/include/php)
include_directories(BEFORE ./ ${PHP_SOURCE} ${PHP_SOURCE}/main ${PHP_SOURCE}/sapi ${PHP_SOURCE}/TSRM ${PHP_SOURCE}/Zend)

add_library(ext_pocketmine_math SHARED ${SRC_LIST} ${HEAD_FILES})