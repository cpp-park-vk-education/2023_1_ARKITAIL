set(MODULE_NAME tree_node_w_director)
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
                      
file(GLOB SOURCES ${SOURCE_DIR}/*.cpp)
                      
add_library(${MODULE_NAME} STATIC ${SOURCES})
target_include_directories(${MODULE_NAME} PUBLIC ${INCLUDE_DIR})
                      
target_link_libraries(${MODULE_NAME} PUBLIC
                        calendula_compiler_flags
                        options_w
                        options_w_builder
                        options_w_director
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
                      
