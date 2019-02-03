cmake_minimum_required(VERSION 3.9)
project(xtl CXX C)

set(CMAKE_CXX_STANDARD 11)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wpedantic -fno-rtti -fno-exceptions")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-Os")

add_library(xtl INTERFACE)
target_include_directories(xtl INTERFACE "${CMAKE_SOURCE_DIR}/include")

add_subdirectory(test)

