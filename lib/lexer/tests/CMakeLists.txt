add_executable(lexer_tests src/lexer_tests.cpp)

target_link_libraries(lexer_tests PUBLIC lexer GTest::gtest_main)

add_test(lexer_tests lexer_tests)
