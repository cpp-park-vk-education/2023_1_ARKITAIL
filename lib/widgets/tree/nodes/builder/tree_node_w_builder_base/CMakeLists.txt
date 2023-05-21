add_library(tree_node_w_builder_base  src/tree_node_w_builder_base.cpp)

target_include_directories(tree_node_w_builder_base  PUBLIC include)

target_link_libraries(tree_node_w_builder_base  PUBLIC
                      calendula_compiler_flags
                      options_w
                      tree_node_dir_w
                      tree_node_subscriptions_dir_w
                      tree_node_other_dir_w
                      node
                      tree_node_w
                      calendar
                      directory
                      user
                      profile
                      profile_manager
                      in_place_edit_title
                      )
