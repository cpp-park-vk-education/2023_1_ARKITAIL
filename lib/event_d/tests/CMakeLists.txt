add_executable(event_d_tests src/event_d_tests.cpp)

target_link_libraries(event_d_tests PUBLIC
                      event_d
                      GTest::gtest_main
                      calendula_compiler_flags)

add_test(event_d_tests event_d_tests)
