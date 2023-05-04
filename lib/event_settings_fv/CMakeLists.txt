add_library(event_settings_fv src/event_settings_fv.cpp)

target_include_directories(event_settings_fv PUBLIC include)

target_link_libraries(event_settings_fv PUBLIC
                      event_settings_fm
                      calendula_compiler_flags)

if(BUILD_TESTS)
  add_subdirectory(tests)
endif(BUILD_TESTS)
