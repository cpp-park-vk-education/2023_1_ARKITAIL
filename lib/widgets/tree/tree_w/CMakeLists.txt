add_library(tree_w  src/tree_w.cpp)

target_include_directories(tree_w  PUBLIC include)

target_link_libraries(tree_w  PUBLIC
                      calendula_compiler_flags
                      tree_node_w
                      tree_node_leaf_w
                      tree_node_dir_w
                      tree_node_other_dir_w
                      node
                      tree
                      managers)
