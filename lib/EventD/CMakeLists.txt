add_library(EventD  src/EventD.cpp)

target_include_directories(EventD  PUBLIC include)

target_link_libraries(EventD  PUBLIC
                      calendula_compiler_flags
                      CommentsContainerW)
