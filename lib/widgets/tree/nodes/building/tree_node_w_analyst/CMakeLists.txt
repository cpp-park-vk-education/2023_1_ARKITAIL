set(MODULE_NAME tree_node_w_analyst)
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(INTERFACE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/interface)
                      
file(GLOB SOURCES ${SOURCE_DIR}/*.cpp)
                      
add_library(${MODULE_NAME} STATIC ${SOURCES})
target_include_directories(${MODULE_NAME} PUBLIC ${INCLUDE_DIR} ${INTERFACE_DIR})
                      
target_link_libraries(
                    ${MODULE_NAME}
                        PUBLIC
                        calendula_compiler_flags
                        node
                        calendar
                        directory
                        user
                        profile
                        profile_manager
                        in_place_edit_title
                        session_scope_map
                        user
                      )
                      