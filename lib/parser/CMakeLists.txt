add_library(parser src/parser.cpp)

target_include_directories(parser PUBLIC include)

target_link_libraries(parser PUBLIC lexer)

if(BUILD_TESTS)
  add_subdirectory(tests)
endif(BUILD_TESTS)
