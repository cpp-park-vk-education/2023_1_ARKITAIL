cmake_minimum_required(VERSION 3.15)

project(Calendula)

find_package(Wt REQUIRED)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(BUILD_TESTS "build tests" OFF)
if(BUILD_TESTS)
    find_package(GTest REQUIRED)
    enable_testing()
endif(BUILD_TESTS)

add_library(calendula_compiler_flags INTERFACE)

target_compile_features(
    calendula_compiler_flags INTERFACE
    cxx_std_17
)

target_compile_options(calendula_compiler_flags INTERFACE
    "$<BUILD_INTERFACE:-g;-Wall;-Wextra;-Wshadow;-Wformat=2;-Wunused>"
)

add_executable(Calendula src/main.cpp)
add_subdirectory(lib)
target_link_libraries(
    Calendula PUBLIC
    application # Все зависимости содержит библиотека application
    session
)
