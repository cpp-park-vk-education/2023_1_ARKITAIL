add_executable(char_reader_tests src/char_reader_tests.cpp)

target_link_libraries(char_reader_tests PUBLIC char_reader GTest::gtest_main)

add_test(char_reader_tests char_reader_tests)
