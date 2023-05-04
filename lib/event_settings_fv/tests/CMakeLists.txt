add_executable(event_settings_fv_tests src/event_settings_fv_tests.cpp)

target_link_libraries(event_settings_fv_tests PUBLIC
                      event_settings_fv
                      GTest::gtest_main
                      calendula_compiler_flags)

add_test(event_settings_fv_tests event_settings_fv_tests)
