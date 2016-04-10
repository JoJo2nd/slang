#
# Copyright 2016 James Moran. All rights reserved.
# License: https://github.com/JoJo2nd/slang/blob/master/LICENSE
#

cmake_minimum_required(VERSION 2.8.12.2)

project(lang)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
  set(BUILD_PLATFORM "windows")
  set(PLATFORM_WINDOWS true)
endif()

function(FLEX_GEN_SOURCE HDRS)
  if(NOT ARGN)
    message(SEND_ERROR "Error: FLEX_GEN_SOURCE() called without any lex files")
    return()
  endif(NOT ARGN)
  
  set(FLEX_EXECUTABLE "${CMAKE_CURRENT_SOURCE_DIR}/deps/bin/flex")
  set(${HDRS})

  foreach(FIL ${ARGN})
    get_filename_component(ABS_FIL ${FIL} ABSOLUTE)
    get_filename_component(FIL_WE ${FIL} NAME_WE)
    get_filename_component(ABS_ROOT ${ABS_FIL} DIRECTORY)

    set(FLEX_OUTPUT_C "${ABS_ROOT}/${FIL_WE}.yy.c")
    set(FLEX_OUTPUT_H "${ABS_ROOT}/${FIL_WE}.yy.h")
    list(APPEND ${HDRS} ${FLEX_OUTPUT_C})

    set_source_files_properties(${ABS_FIL} PROPERTIES HEADER_FILE_ONLY TRUE)

    add_custom_command(
      OUTPUT ${FLEX_OUTPUT_C} ${FLEX_OUTPUT_H}
      COMMAND ${FLEX_EXECUTABLE} ARGS --header-file="${FLEX_OUTPUT_H}" -o"${FLEX_OUTPUT_C}" "${FIL}"
      DEPENDS ${FIL}
      COMMENT "Flex ${FIL} -> ${FLEX_OUTPUT_H} & ${FLEX_OUTPUT_C}")
  endforeach()

  set_source_files_properties(${${HDRS}} PROPERTIES GENERATED TRUE)
  set(${HDRS} ${${HDRS}} PARENT_SCOPE)
endfunction()

function(BISON_GEN_SOURCE HDRS)
  # Binson needs to work in the current directory it seems.
  if(NOT ARGN)
    message(SEND_ERROR "Error: BISON_GEN_SOURCE() called without any grammer files")
    return()
  endif(NOT ARGN)
  
  set(BISON_EXECUTABLE "${CMAKE_CURRENT_SOURCE_DIR}/deps/bin/bison")
  set(${HDRS})

  foreach(FIL ${ARGN})
    get_filename_component(ABS_FIL ${FIL} ABSOLUTE)
    get_filename_component(FIL_WE ${FIL} NAME_WE)
    get_filename_component(ABS_ROOT ${ABS_FIL} DIRECTORY)

    set(BISON_OUTPUT_C "${ABS_ROOT}/${FIL_WE}.tab.c")
    set(BISON_OUTPUT_H "${ABS_ROOT}/${FIL_WE}.tab.h")
    list(APPEND ${HDRS} ${BISON_OUTPUT_C} ${BISON_OUTPUT_H})

    set_source_files_properties(${ABS_FIL} PROPERTIES HEADER_FILE_ONLY TRUE)

    add_custom_command(
      OUTPUT ${BISON_OUTPUT_C} ${BISON_OUTPUT_H}
      COMMAND ${BISON_EXECUTABLE} ARGS -vd --report=all -o"${BISON_OUTPUT_C}" ${FIL}
      DEPENDS ${FIL}
      COMMENT "Bison ${FIL} -> ${BISON_OUTPUT_H} & ${BISON_OUTPUT_C}")
  endforeach()

  set_source_files_properties(${${HDRS}} PROPERTIES GENERATED TRUE)
  set(${HDRS} ${${HDRS}} PARENT_SCOPE)
endfunction()


set( INCLUDE_DIRS
    "${CMAKE_CURRENT_SOURCE_DIR}/deps/include"
)
set( LINK_DIRS
    "${CMAKE_CURRENT_SOURCE_DIR}/deps/lib"
)
file(GLOB SRC_FILES 
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c"
)
file(GLOB FLEX_SRC_FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.l"
)
file(GLOB BISON_SRC_FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.y"
)
FLEX_GEN_SOURCE(FLEX_CODE_FILES ${FLEX_SRC_FILES})
BISON_GEN_SOURCE(BISON_CODE_FILES ${BISON_SRC_FILES})

file(GLOB HLSL_BE_SRC_FILES 
    "${CMAKE_CURRENT_SOURCE_DIR}/src/backends/hlsl/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/backends/hlsl/*.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/backends/hlsl/*.cpp"
)

file(GLOB GLSL_BE_SRC_FILES 
    "${CMAKE_CURRENT_SOURCE_DIR}/src/backends/glsl/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/backends/glsl/*.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/backends/glsl/*.cpp"
)

add_definitions(-D_CRT_SECURE_NO_WARNINGS)

include_directories(${INCLUDE_DIRS})
link_directories(${LINK_DIRS})


add_library(slang2hlsl MODULE ${HLSL_BE_SRC_FILES})
add_library(slang2glsl MODULE ${GLSL_BE_SRC_FILES})
add_executable(slangc ${SRC_FILES} ${FLEX_SRC_FILES} ${FLEX_CODE_FILES} ${BISON_SRC_FILES} ${BISON_CODE_FILES})
add_dependencies(slangc slang2hlsl)