add_library(tree_node_w_director  src/tree_node_w_director.cpp)

target_include_directories(tree_node_w_director  PUBLIC include)

target_link_libraries(tree_node_w_director  PUBLIC
                      tree
                      node
                      )
