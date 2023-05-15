set(MODULE_NAME application)
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

file(GLOB SOURCES ${SOURCE_DIR}/*.cpp)

add_library(${MODULE_NAME} STATIC ${SOURCES})
target_include_directories(${MODULE_NAME} PUBLIC ${INCLUDE_DIR})
target_link_libraries(${MODULE_NAME} PUBLIC 
                                        wt 
                                        wthttp 
                                        unmet_deps 
                                        swapable 
                                        connections_mediator 
                                        page_widget
                                        main_p
                                        other_p
                                        navbar_w)

