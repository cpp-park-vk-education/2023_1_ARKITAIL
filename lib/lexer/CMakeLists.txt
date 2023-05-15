add_library(lexer src/lexer.cpp)

target_include_directories(lexer PUBLIC include)

target_link_libraries(lexer PUBLIC char_reader)

if(BUILD_TESTS)
  add_subdirectory(tests)
endif(BUILD_TESTS)
