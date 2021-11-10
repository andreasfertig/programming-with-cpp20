# Copyright (c) Andreas Fertig.
# SPDX-License-Identifier: MIT

cmake_minimum_required(VERSION 3.16.2 FATAL_ERROR)

set(CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 20)

set(EXEC_NAME ${CMAKE_CURRENT_SOURCE_DIR})

project(${EXEC_NAME} CXX)

# build the filename
get_filename_component(EXEC_NAME "${EXEC_NAME}" NAME)

function(check_compiler COMPILER version)
    if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "${COMPILER}")
        if (CMAKE_CXX_COMPILER_VERSION VERSION_LESS ${version})
            message(FATAL_ERROR "${COMPILER} version must be at least ${version}!")
        endif()

        set(HAVE_COMPILER On PARENT_SCOPE)
    endif()
endfunction(check_compiler)

check_compiler("GNU" 10.2)
check_compiler("Clang" 12.0)
check_compiler("MSVC" 19.28.29914.0)


if(NOT HAVE_COMPILER)
    message(ERROR "You are using an unsupported compiler!")
endif()


if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    set(IS_GNU On)
    add_definitions(-DIS_GCC=true)
else()
    set(IS_GNU Off)
    add_definitions(-DIS_GCC=false)
endif()

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang" OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "AppleClang")
    set(IS_CLANG On)
    add_definitions(-DIS_CLANG=true)
else()
    set(IS_CLANG Off)
    add_definitions(-DIS_CLANG=false)
endif()

if(MSVC)
    add_definitions(-DIS_MSVC=true)
    add_definitions(/WX)
    add_definitions(/W4)
    add_definitions(/wd4189)
    add_definitions(/wd4100)
    add_definitions(/wd4996) # 'fopen': This function or variable may be unsafe. Consider using fopen_s instead. To disable deprecation, use _CRT_SECURE_NO_WARNINGS.
    add_definitions(/wd4267)
    add_definitions(/wd4505)
    add_definitions(/await) # enable coroutine support

    # Use sane and nice C++ for MSVC.
    # This makes alternative tokens (not, and, ...) as actual keywords and
    # enables more conformant C++ in general
    add_definitions(/permissive-)

    
else()
    add_definitions(-DIS_MSVC=false)
    add_definitions(-Werror)
    add_definitions(-Wall)
    add_definitions(-Wextra)
    add_definitions(-Wold-style-cast)
    add_definitions(-Wno-unused-variable)
    add_definitions(-Wno-unused-parameter)
    add_definitions(-Wno-unused-value)
    add_definitions(-Wno-cpp)

    if(IS_CLANG)
      add_definitions(-Wno-unused-private-field)
      add_definitions(-Wno-unneeded-internal-declaration)
      
    else()
      add_definitions(-fcoroutines) # required for GCC-10    
      
    endif()
endif()

add_executable(${EXEC_NAME} main.cpp)

