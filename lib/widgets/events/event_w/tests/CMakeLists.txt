add_executable(event_w_tests test.cpp)

target_link_libraries(event_w_tests PUBLIC
                      event_w
                      GTest::gtest_main)

include(GoogleTest)

gtest_discover_tests(event_w_tests)
