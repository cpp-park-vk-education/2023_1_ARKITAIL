add_library(event_settings_fm src/event_settings_fm.cpp)

target_include_directories(event_settings_fm PUBLIC include)

target_link_libraries(event_settings_fm PUBLIC
                      wt
                      event
                      calendula_compiler_flags)

if(BUILD_TESTS)
  add_subdirectory(tests)
endif(BUILD_TESTS)
