############################################################################
#  testsuite/CMakeLists.txt
#
#  CMake file for building the STX String test suite.
#
#  Copyright (C) 2014 Timo Bingmann <tb@panthema.net>
#
#  Distributed under the Boost Software License, Version 1.0.
#  (See accompanying file LICENSE_1_0.txt or copy at
#  http://www.boost.org/LICENSE_1_0.txt)
############################################################################

include_directories("${PROJECT_SOURCE_DIR}/include")

add_executable(simple simple.cpp)
target_link_libraries(simple ${BUILD_LIBRARIES})
add_test(simple simple)

add_executable(natcmp natcmp.cpp strnatcmp.c)
target_link_libraries(natcmp ${BUILD_LIBRARIES})
add_test(natcmp natcmp)

add_executable(compress compress.cpp)
target_link_libraries(compress ${BUILD_LIBRARIES})
add_test(compress compress)

add_executable(bz2compress bz2compress.cpp)
target_link_libraries(bz2compress ${BUILD_LIBRARIES})
add_test(bz2compress bz2compress)