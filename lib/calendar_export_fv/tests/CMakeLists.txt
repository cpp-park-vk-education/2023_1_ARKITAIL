add_executable(calendar_export_fv_tests src/calendar_export_fv_tests.cpp)

target_link_libraries(calendar_export_fv_tests PUBLIC
                      calendar_export_fv
                      GTest::gtest_main
                      calendula_compiler_flags)

add_test(calendar_export_fv_tests calendar_export_fv_tests)
