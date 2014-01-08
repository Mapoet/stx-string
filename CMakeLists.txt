############################################################################
#  CMakeLists.txt
#
#  Base CMake file for building the STX String test suite.
#
#  Copyright (C) 2014 Timo Bingmann <tb@panthema.net>
#
#  Distributed under the Boost Software License, Version 1.0.
#  (See accompanying file LICENSE_1_0.txt or copy at
#  http://www.boost.org/LICENSE_1_0.txt)
############################################################################

# require cmake 2.6.2 (but please use 2.8.x)
cmake_minimum_required(VERSION 2.6.2 FATAL_ERROR)

# the STX String (testsuite) project
project(stx-string)

# prohibit in-source builds
if("${PROJECT_SOURCE_DIR}" STREQUAL "${PROJECT_BINARY_DIR}")
  message(SEND_ERROR "In-source builds are not allowed.")
endif()

# default to Debug building for single-config generators
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message("Defaulting CMAKE_BUILD_TYPE to Debug")
  set(CMAKE_BUILD_TYPE "Debug")
endif()

# enable high warnings level for test suite
if(MSVC)
  # Force to always compile with W4
  if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
    string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
  else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
  endif()
elseif(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
  # Update if necessary
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -W -Wall -Wextra -Wold-style-cast")
endif()

# enable use of "make test"
enable_testing()

# check if zlib is available
find_package(ZLIB)
if(ZLIB_FOUND)
  add_definitions(-DHAVE_ZLIB)
  include_directories(${ZLIB_INCLUDE_DIRS})
  set(BUILD_LIBRARIES ${BUILD_LIBRARIES} ${ZLIB_LIBRARIES})
endif()

# check if bzip2 is available
find_package(BZip2)
if(BZIP2_FOUND)
  add_definitions(-DHAVE_BZIP2)
  include_directories(${BZIP2_INCLUDE_DIRS})
  set(BUILD_LIBRARIES ${BUILD_LIBRARIES} ${BZIP2_LIBRARIES})
endif()

# build test suite
add_subdirectory(testsuite)
