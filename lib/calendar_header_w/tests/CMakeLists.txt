add_executable(calendar_header_w_tests src/calendar_header_w_tests.cpp)

target_link_libraries(calendar_header_w_tests PUBLIC
                      calendar_header_w
                      GTest::gtest_main
                      calendula_compiler_flags)

add_test(calendar_header_w_tests calendar_header_w_tests)
