add_library(parser
  character_reader.cpp
  lexer.cpp
  parser.cpp)

target_link_libraries(parser calendula_compiler_flags)
target_include_directories(parser PUBLIC .)

if(BUILD_TESTS)
  add_executable(character_reader_test character_reader.test.cpp)
  target_link_libraries(character_reader_test GTest::gtest_main
                                              parser
                                              calendula_compiler_flags)
  add_test(character_reader_test character_reader_test)

  add_executable(lexer_test lexer.test.cpp)
  target_link_libraries(lexer_test GTest::gtest_main
                                   parser
                                   calendula_compiler_flags)
  add_test(lexer_test lexer_test)
  
  add_executable(parser_test parser.test.cpp)
  target_link_libraries(parser_test GTest::gtest_main
                                    parser
                                    calendula_compiler_flags)
  add_test(parser_test parser_test)
endif()
