add_library(OtherP src/OtherP.cpp)

target_include_directories(OtherP PUBLIC include)

target_link_libraries(OtherP PUBLIC
                      CalendarW
                      calendula_compiler_flags)

if(BUILD_TESTS)
  add_subdirectory(tests)
endif(BUILD_TESTS)
