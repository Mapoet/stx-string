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

add_executable(SimpleTest SimpleTest.cc)
target_link_libraries(SimpleTest ${BUILD_LIBRARIES})
add_test(SimpleTest SimpleTest)

add_executable(NatcmpTest NatcmpTest.cc strnatcmp.c)
target_link_libraries(NatcmpTest ${BUILD_LIBRARIES})
add_test(NatcmpTest NatcmpTest)

add_executable(CompressTest CompressTest.cc)
target_link_libraries(CompressTest ${BUILD_LIBRARIES})
add_test(CompressTest CompressTest)

add_executable(Bz2CompressTest Bz2CompressTest.cc)
target_link_libraries(Bz2CompressTest ${BUILD_LIBRARIES})
add_test(Bz2CompressTest Bz2CompressTest)