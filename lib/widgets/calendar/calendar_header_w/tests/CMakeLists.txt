add_executable(calendar_header_w_tests test.cpp)

target_link_libraries(calendar_header_w_tests PUBLIC
                      calendar_header_w
                      GTest::gtest_main
                      calendula_compiler_flags)

include(GoogleTest)

gtest_discover_tests(calendar_header_w_tests)
