add_executable(event_tests src/event_tests.cpp)

target_link_libraries(event_tests PUBLIC
                      event
                      GTest::gtest_main
                      calendula_compiler_flags)

add_test(event_tests event_tests)
