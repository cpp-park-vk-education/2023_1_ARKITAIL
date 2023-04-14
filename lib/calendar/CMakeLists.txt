add_library(calendar src/calendar.cpp)

target_include_directories(calendar PUBLIC include)

target_link_libraries(calendar PUBLIC
                      calendula_compiler_flags)

if(BUILD_TESTS)
  add_subdirectory(tests)
endif(BUILD_TESTS)
