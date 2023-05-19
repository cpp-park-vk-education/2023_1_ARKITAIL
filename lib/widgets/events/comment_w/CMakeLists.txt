add_library(comment_w  src/comment_w.cpp)

target_include_directories(comment_w  PUBLIC include)

target_link_libraries(comment_w  PUBLIC
                      calendula_compiler_flags)
