add_executable(calendar_export_fm_tests src/calendar_export_fm_tests.cpp)

target_link_libraries(calendar_export_fm_tests PUBLIC
                      calendar_export_fm
                      GTest::gtest_main
                      calendula_compiler_flags)

add_test(calendar_export_fm_tests calendar_export_fm_tests)
