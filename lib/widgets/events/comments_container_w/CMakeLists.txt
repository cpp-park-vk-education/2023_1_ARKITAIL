add_library(comments_container_w  src/comments_container_w.cpp)

target_include_directories(comments_container_w  PUBLIC include)

target_link_libraries(comments_container_w  PUBLIC
                      calendula_compiler_flags
                      comment_w)
