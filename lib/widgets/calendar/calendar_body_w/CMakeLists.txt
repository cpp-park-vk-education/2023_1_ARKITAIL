set(MODULE_NAME calendar_body_w)
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(INTERFACE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/interface)
                      
file(GLOB SOURCES ${SOURCE_DIR}/*.cpp)
                      
add_library(${MODULE_NAME} STATIC ${SOURCES})
target_include_directories(${MODULE_NAME} PUBLIC ${INCLUDE_DIR} ${INTERFACE_DIR})
                      
target_link_libraries(${MODULE_NAME} PUBLIC
                        calendula_compiler_flags
                        time_utils
                        event
                        )
