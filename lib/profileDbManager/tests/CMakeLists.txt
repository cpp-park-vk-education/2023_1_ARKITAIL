add_executable(${MODULE_NAME}_tests test.cpp)
target_link_libraries(${MODULE_NAME}_tests PUBLIC GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(${MODULE_NAME}_tests)
