add_library(tree_node_w_analyst  src/tree_node_w_analyst.cpp)

target_include_directories(tree_node_w_analyst  PUBLIC include)

target_link_libraries(tree_node_w_analyst  PUBLIC
                      calendula_compiler_flags
                      node
                      tree_node_w
                      calendar
                      directory
                      user
                      profile
                      profile_manager
                      in_place_edit_title
                      session_scope_map
                      user
                      )
