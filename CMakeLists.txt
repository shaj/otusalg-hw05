cmake_minimum_required(VERSION 3.2)

project(l5)

add_executable(l5 main.cpp)

set_target_properties(l5 PROPERTIES
  CXX_STANDARD 14
  CXX_STANDARD_REQUIRED ON
  COMPILE_OPTIONS -Wpedantic -Wall -Wextra
)

configure_file("${PROJECT_SOURCE_DIR}/1.txt" "${PROJECT_BINARY_DIR}/1.txt" COPYONLY)
configure_file("${PROJECT_SOURCE_DIR}/shuffle.txt" "${PROJECT_BINARY_DIR}/shuffle.txt" COPYONLY)


