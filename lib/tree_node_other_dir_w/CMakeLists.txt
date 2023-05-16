add_library(tree_node_other_dir_w  src/tree_node_other_dir_w.cpp)

target_include_directories(tree_node_other_dir_w  PUBLIC include)

target_link_libraries(tree_node_other_dir_w  PUBLIC
                      calendula_compiler_flags
                      tree_node_dir_w)
