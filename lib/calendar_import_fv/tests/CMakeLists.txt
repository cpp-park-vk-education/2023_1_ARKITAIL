add_executable(calendar_import_fv_tests src/calendar_import_fv_tests.cpp)

target_link_libraries(calendar_import_fv_tests PUBLIC
                      calendar_import_fv
                      GTest::gtest_main
                      calendula_compiler_flags)

add_test(calendar_import_fv_tests calendar_import_fv_tests)
