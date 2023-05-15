add_executable(event_settings_fm_tests src/event_settings_fm_tests.cpp)

target_link_libraries(event_settings_fm_tests PUBLIC
                      event_settings_fm
                      GTest::gtest_main
                      calendula_compiler_flags)

add_test(event_settings_fm_tests event_settings_fm_tests)
