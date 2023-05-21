cmake_minimum_required(VERSION 3.15)

project(Calendula)

find_package(Boost REQUIRED)
find_package(Wt REQUIRED)
find_package(PostgreSQL REQUIRED)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

SET (WT_CONNECTOR "wthttp" CACHE STRING "Connector used (wthttp or wtfcgi)")

option(BUILD_TESTS "build tests" ON)
if(BUILD_TESTS)
    enable_testing()
    find_package(GTest REQUIRED)
endif(BUILD_TESTS)

add_library(calendula_compiler_flags INTERFACE)

target_compile_features(
    calendula_compiler_flags
    INTERFACE
    cxx_std_17
)

target_compile_options(calendula_compiler_flags INTERFACE
    "$<BUILD_INTERFACE:-Wall;-Wextra;-Wshadow;-Wformat=2;-Wunused>"
)

add_executable(Calendula src/main.cpp)
add_subdirectory(lib)

target_link_libraries(
    Calendula PUBLIC
    calendula_compiler_flags

    wthttp
    wt

    application  # Все зависимости содержит библиотека application
)

target_include_directories(${PROJECT_NAME} PUBLIC /usr/local/inlcude/Wt)

