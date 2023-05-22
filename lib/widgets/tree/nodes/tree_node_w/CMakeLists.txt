add_library(tree_node_w  src/tree_node_w.cpp)

target_include_directories(tree_node_w  PUBLIC include)

target_link_libraries(tree_node_w  PUBLIC
                      calendula_compiler_flags
                      options_w
                      tree_node_dir_w
                      tree_node_subscriptions_dir_w
                      tree_node_other_dir_w
                      node
                      tree
                      calendar
                      directory
                      user
                      profile
                      profile_manager
                      in_place_edit_title
                      tree_node_w_builder_base
                      tree_node_dir_w_builder
                      tree_node_sub_dir_w_builder
                      tree_node_other_dir_w_builder
                      tree_node_leaf_w_builder
                      options_w_director
                      )
