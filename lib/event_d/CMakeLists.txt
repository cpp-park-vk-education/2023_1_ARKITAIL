add_library(event_d src/event_d.cpp)

target_include_directories(event_d PUBLIC include)

target_link_libraries(event_d PUBLIC
                      event_settings_fv
                      calendula_compiler_flags)

if(BUILD_TESTS)
  add_subdirectory(tests)
endif(BUILD_TESTS)
