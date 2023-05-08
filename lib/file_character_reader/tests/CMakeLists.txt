add_executable(file_character_reader_tests src/file_character_reader_tests.cpp)

target_link_libraries(file_character_reader_tests PUBLIC
                      file_character_reader
                      GTest::gtest_main
                      calendula_compiler_flags)

add_test(file_character_reader_tests file_character_reader_tests)
