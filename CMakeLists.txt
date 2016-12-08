cmake_minimum_required(VERSION 2.8)

option(SPIRA_TEST "Build all tests." ON)

set(PROJECT_NAME SpiraFRP)
project(${PROJECT_NAME})
set(SPIRA_VERSION_MAJOR 2)
set(SPIRA_VERSION_MINOR 2)
set(SPIRA_VERSION_PATCH 0)

# Enable C++11
include(CheckCXXCompilerFlag)
check_cxx_compiler_flag("-std=c++11" STD_CXX11)
if(STD_CXX11)
  add_definitions("-std=c++11")
else()
  add_definitions("-std=c++0x")
endif()

# Project include directory
include_directories(include)

install(
  DIRECTORY "${PROJECT_SOURCE_DIR}/include/spira"
  DESTINATION include
  FILES_MATCHING PATTERN "*.*hpp"
)

add_subdirectory(external)
add_subdirectory(src)
add_subdirectory(tests)
