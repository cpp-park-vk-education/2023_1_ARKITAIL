add_executable(calendar_import_fm_tests src/calendar_import_fm_tests.cpp)

target_link_libraries(calendar_import_fm_tests PUBLIC
                      calendar_import_fm
                      GTest::gtest_main
                      calendula_compiler_flags)

add_test(calendar_import_fm_tests calendar_import_fm_tests)
