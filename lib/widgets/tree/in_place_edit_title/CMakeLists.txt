add_library(in_place_edit_title  src/in_place_edit_title.cpp)

target_include_directories(in_place_edit_title  PUBLIC include)

target_link_libraries(in_place_edit_title  PUBLIC
                      calendula_compiler_flags)
