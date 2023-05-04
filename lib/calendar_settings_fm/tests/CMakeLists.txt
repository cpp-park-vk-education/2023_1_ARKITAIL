add_executable(calendar_settings_fm_tests src/calendar_settings_fm_tests.cpp)

target_link_libraries(calendar_settings_fm_tests PUBLIC
                      calendar_settings_fm
                      GTest::gtest_main
                      calendula_compiler_flags)

add_test(calendar_settings_fm_tests calendar_settings_fm_tests)
