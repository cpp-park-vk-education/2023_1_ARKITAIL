add_library(calendar_settings_fm src/calendar_settings_fm.cpp)

target_include_directories(calendar_settings_fm PUBLIC include)

target_link_libraries(calendar_settings_fm PUBLIC
                      wt
                      calendar
                      calendula_compiler_flags)

if(BUILD_TESTS)
  add_subdirectory(tests)
endif(BUILD_TESTS)
