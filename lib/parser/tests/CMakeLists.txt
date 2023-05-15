add_executable(parser_tests src/parser_tests.cpp)

target_link_libraries(parser_tests PUBLIC parser GTest::gtest_main)

add_test(parser_tests parser_tests)
