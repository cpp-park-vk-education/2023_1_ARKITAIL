add_executable(create_calendar_d_tests src/create_calendar_d_tests.cpp)

target_link_libraries(create_calendar_d_tests PUBLIC
                      create_calendar_d
                      GTest::gtest_main
                      calendula_compiler_flags)

add_test(create_calendar_d_tests create_calendar_d_tests)
