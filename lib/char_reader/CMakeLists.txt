add_library(char_reader src/char_reader.cpp)

target_include_directories(char_reader PUBLIC include)

target_link_libraries(char_reader PUBLIC calendula_compiler_flags)

if(BUILD_TESTS)
  add_subdirectory(tests)
endif(BUILD_TESTS)
