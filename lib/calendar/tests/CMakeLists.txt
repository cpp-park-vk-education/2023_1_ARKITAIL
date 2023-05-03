add_executable(calendar_tests src/calendar_tests.cpp)

target_link_libraries(calendar_tests PUBLIC
                      calendar
                      GTest::gtest_main
                      calendula_compiler_flags)

add_test(calendar_tests calendar_tests)
