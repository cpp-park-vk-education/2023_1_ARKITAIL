add_executable(event_w_tests test.cpp)

target_link_libraries(event_w_tests PUBLIC
                      event_w
                      wt
                      wthttp
                      GTest::gtest_main
                      GTest::gmock_main)

include(GoogleTest)

gtest_discover_tests(event_w_tests)
