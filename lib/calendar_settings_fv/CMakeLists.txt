add_library(calendar_settings_fv src/calendar_settings_fv.cpp)

target_include_directories(calendar_settings_fv PUBLIC include)

target_link_libraries(calendar_settings_fv PUBLIC
                      calendar_settings_fm
                      calendula_compiler_flags)

if(BUILD_TESTS)
  add_subdirectory(tests)
endif(BUILD_TESTS)
