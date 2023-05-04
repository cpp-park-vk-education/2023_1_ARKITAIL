add_library(CommentsContainerW  src/CommentsContainerW.cpp)

target_include_directories(CommentsContainerW  PUBLIC include)

target_link_libraries(CommentsContainerW  PUBLIC
                      calendula_compiler_flags
                      CommentW)
