add_library(edit_calendar_d src/edit_calendar_d.cpp)

target_include_directories(edit_calendar_d PUBLIC include)

target_link_libraries(edit_calendar_d PUBLIC
                      calendar_settings_fv
                      calendar_export_fv
                      calendula_compiler_flags)

if(BUILD_TESTS)
  add_subdirectory(tests)
endif(BUILD_TESTS)
