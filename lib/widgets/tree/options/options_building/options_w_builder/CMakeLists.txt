set(MODULE_NAME options_w_builder)
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(BASE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/base)
                      
file(GLOB SOURCES ${SOURCE_DIR}/*.cpp)
                      
add_library(${MODULE_NAME} STATIC ${SOURCES})
target_include_directories(${MODULE_NAME} PUBLIC ${INCLUDE_DIR} ${BASE_DIR})
                      
target_link_libraries(${MODULE_NAME} PUBLIC
                        calendula_compiler_flags
                        options_w
                      )
                      
