add_library(MainP src/MainP.cpp)

target_include_directories(MainP PUBLIC include)

target_link_libraries(MainP PUBLIC
                      CalendarW
                      calendula_compiler_flags)

if(BUILD_TESTS)
  add_subdirectory(tests)
endif(BUILD_TESTS)
