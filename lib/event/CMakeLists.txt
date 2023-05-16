add_library(event src/event.cpp)

target_include_directories(event PUBLIC include)

target_link_libraries(event PUBLIC
                      wt
                      calendula_compiler_flags)

if(BUILD_TESTS)
  add_subdirectory(tests)
endif(BUILD_TESTS)
