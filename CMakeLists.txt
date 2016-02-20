cmake_minimum_required(VERSION 2.8.12.2)

project(lang)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
  set(BUILD_PLATFORM "windows")
  set(PLATFORM_WINDOWS true)
endif()

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

source_group(source  FILES ${MATERIAL_BUILDER_SRC_FILES})

include_directories(${INCLUDE_DIRS})
link_directories(${LINK_DIRS})
add_executable(langc ${SRC_FILES})