add_library(CommentW  src/CommentW.cpp)

target_include_directories(CommentW  PUBLIC include)

target_link_libraries(CommentW  PUBLIC
                      calendula_compiler_flags)
