cmake_minimum_required(VERSION 3.15)

project(Calendula)

find_package(Wt REQUIRED)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(BUILD_TESTS "build tests" OFF)
if(BUILD_TESTS)
  enable_testing()
  find_package(GTest REQUIRED)
endif(BUILD_TESTS)

add_library(calendula_compiler_flags INTERFACE)

target_compile_features(calendula_compiler_flags INTERFACE
                        cxx_std_17)

target_compile_options(calendula_compiler_flags INTERFACE
  "$<BUILD_INTERFACE:-Wall;-Wextra;-Wformat=2;-Wunused>"
)

add_subdirectory(lib)

add_executable(Calendula.wt src/main.cpp)

target_link_libraries(Calendula.wt PUBLIC
                      wthttp
                      calendula_application
                      calendula_compiler_flags)
