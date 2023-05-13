add_library(tree_node_leave_w  src/tree_node_leave_w.cpp)

target_include_directories(tree_node_leave_w  PUBLIC include)

target_link_libraries(tree_node_leave_w  PUBLIC
                      calendula_compiler_flags
                      tree_node_w)
