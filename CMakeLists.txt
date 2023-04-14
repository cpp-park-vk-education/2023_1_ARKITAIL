cmake_minimum_required(VERSION 3.15)

project(Calendula VERSION 1.0)

find_package(PostgreSQL REQUIRED)
find_package(Boost REQUIRED)
find_package(Wt REQUIRED)

option(BUILD_TESTS "build tests")
if(BUILD_TESTS)
  enable_testing()
  find_package(GTest REQUIRED)
endif(BUILD_TESTS)

add_library(calendula_compiler_flags INTERFACE)
target_compile_features(calendula_compiler_flags INTERFACE cxx_std_17)

set(gcc_like_cxx "$<COMPILE_LANG_AND_ID:CXX,ARMClang,AppleClang,Clang,GNU,LCC>")
set(msvc_cxx "$<COMPILE_LANG_AND_ID:CXX,MSVC>")
target_compile_options(calendula_compiler_flags INTERFACE
  "$<${gcc_like_cxx}:$<BUILD_INTERFACE:-Wall;-Wextra;-Wshadow;-Wformat=2;-Wunused>>"
  "$<${msvc_cxx}:$<BUILD_INTERFACE:-W3>>"
)

add_subdirectory(lib)

add_executable(Calendula src/main.cpp)

target_link_libraries(Calendula PUBLIC
                      calendula_compiler_flags)
