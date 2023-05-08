add_library(file_character_reader src/file_character_reader.cpp)

target_include_directories(file_character_reader PUBLIC include)

target_link_libraries(file_character_reader PUBLIC
                      i_character_reader
                      calendula_compiler_flags)

if(BUILD_TESTS)
  add_subdirectory(tests)
endif(BUILD_TESTS)
