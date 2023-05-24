add_library(tree_node_w_director  src/tree_node_w_director.cpp)

target_include_directories(tree_node_w_director  PUBLIC include)

target_link_libraries(tree_node_w_director  PUBLIC
                      calendula_compiler_flags
                      options_w
                      options_w_builder
                      options_w_director
                      tree_node_dir_w
                      node
                      calendar
                      directory
                      user
                      profile
                      profile_manager
                      in_place_edit_title
                      tree_node_w_analyst
                      tree_node_w_builder
                      )
