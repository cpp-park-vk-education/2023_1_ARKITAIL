add_executable(edit_calendar_d_tests src/edit_calendar_d_tests.cpp)

target_link_libraries(edit_calendar_d_tests PUBLIC
                      edit_calendar_d
                      GTest::gtest_main
                      calendula_compiler_flags)

add_test(edit_calendar_d_tests edit_calendar_d_tests)
