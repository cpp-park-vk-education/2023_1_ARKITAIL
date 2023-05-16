add_library(tree_node_profile_w  src/tree_node_profile_w.cpp)

target_include_directories(tree_node_profile_w  PUBLIC include)

target_link_libraries(tree_node_profile_w  PUBLIC
                      tree_node_leaf_w
                      calendula_compiler_flags)
