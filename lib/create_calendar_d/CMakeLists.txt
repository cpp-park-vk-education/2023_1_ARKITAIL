add_library(create_calendar_d src/create_calendar_d.cpp)

target_include_directories(create_calendar_d PUBLIC include)

target_link_libraries(create_calendar_d PUBLIC
                      calendar_settings_fv
                      calendar_import_fv
                      calendula_compiler_flags)

if(BUILD_TESTS)
  add_subdirectory(tests)
endif(BUILD_TESTS)
