cmake_minimum_required(VERSION 3.2)

project(l5)

# list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")
# find_package(GMP REQUIRED)

add_executable(l5 main.cpp)

set_target_properties(l5 PROPERTIES
  CXX_STANDARD 14
  CXX_STANDARD_REQUIRED ON
  COMPILE_OPTIONS -Wpedantic -Wall -Wextra
)

# target_link_libraries(l5 gmp)


