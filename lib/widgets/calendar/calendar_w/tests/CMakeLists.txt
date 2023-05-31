add_executable(calendar_w_tests src/tests.cpp)

target_link_libraries(calendar_w_tests PUBLIC
                      calendar_w
                      GTest::gtest_main
                      GTest::gmock_main
                      calendula_compiler_flags)

add_test(calendar_w_tests calendar_w_tests)
