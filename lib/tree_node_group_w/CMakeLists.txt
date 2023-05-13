add_library(tree_node_group_w  src/tree_node_group_w.cpp)

target_include_directories(tree_node_group_w  PUBLIC include)

target_link_libraries(tree_node_group_w  PUBLIC
                      tree_node_leave_w
                      calendula_compiler_flags)
