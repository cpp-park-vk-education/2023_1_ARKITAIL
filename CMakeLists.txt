cmake_minimum_required(VERSION 3.15)

project(Calendula)

find_package(PostgreSQL REQUIRED)
find_package(Boost REQUIRED)
find_package(Wt REQUIRED)

option(BUILD_TESTS "build tests" OFF)
if(BUILD_TESTS)
  enable_testing()
  find_package(GTest REQUIRED)
endif(BUILD_TESTS)

add_library(calendula_compiler_flags INTERFACE)

target_compile_features(calendula_compiler_flags INTERFACE
                        cxx_std_17)

target_compile_options(calendula_compiler_flags INTERFACE
  "$<BUILD_INTERFACE:-Wall;-Wextra;-Wshadow;-Wformat=2;-Wunused>"
)

add_subdirectory(lib)

add_executable(Calendula src/main.cpp)

target_link_libraries(Calendula PUBLIC
                      calendula_compiler_flags)
