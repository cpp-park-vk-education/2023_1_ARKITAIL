add_library(tree_node_w_builder  src/tree_node_w_builder.cpp)

target_include_directories(tree_node_w_builder  PUBLIC include)

target_link_libraries(tree_node_w_builder  PUBLIC
                      tree
                      )
