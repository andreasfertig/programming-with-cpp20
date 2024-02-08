# Copyright (c) Andreas Fertig.
# SPDX-License-Identifier: MIT

cmake_minimum_required(VERSION 3.28.2 FATAL_ERROR)

project("Programming with C++20 - Concepts, Coroutines, Ranges, and more" CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)


# https://stackoverflow.com/questions/7787823/cmake-how-to-get-the-name-of-all-subdirectories-of-a-directory
macro(SUBDIRLIST result curdir)
  file(GLOB children RELATIVE ${curdir} ${curdir}/*)
  set(dirlist "")
  foreach(child ${children})
    if(IS_DIRECTORY ${curdir}/${child})
      list(APPEND dirlist ${child})
    endif()
  endforeach()
  set(${result} ${dirlist})
endmacro()


SUBDIRLIST(SUBDIRS ${CMAKE_SOURCE_DIR})

foreach(subdir ${SUBDIRS})
  if(EXISTS ${CMAKE_SOURCE_DIR}/${subdir}/CMakeLists.txt)
    add_subdirectory(${subdir})
  else()
    message(DEBUG "Subdirectory ${subdir} does not contain a 'CMakeLists.txt'")
  endif()
endforeach()
