add_executable(calendar_settings_fv_tests src/calendar_settings_fv_tests.cpp)

target_link_libraries(calendar_settings_fv_tests PUBLIC
                      calendar_settings_fv
                      GTest::gtest_main
                      calendula_compiler_flags)

add_test(calendar_settings_fv_tests calendar_settings_fv_tests)
