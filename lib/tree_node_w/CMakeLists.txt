add_library(tree_node_w  src/tree_node_w.cpp)

target_include_directories(tree_node_w  PUBLIC include)

target_link_libraries(tree_node_w  PUBLIC
                      calendula_compiler_flags)
