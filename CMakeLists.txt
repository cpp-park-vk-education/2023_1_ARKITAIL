cmake_minimum_required(VERSION 3.15)

project(Calendula)

find_package(Boost REQUIRED)
find_package(Wt REQUIRED)
find_package(PostgreSQL REQUIRED)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

SET (WT_CONNECTOR "wthttp" CACHE STRING "Connector used (wthttp or wtfcgi)")

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

add_executable(Calendula.wt src/main.cpp)

target_link_libraries(Calendula.wt PUBLIC
                      ${WT_CONNECTOR} wt
                      NavbarWidget
                      MainWidget
                      public_calendar
                      private_calendar
                      calendula_compiler_flags)


