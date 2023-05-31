set(MODULE_NAME calendar_w)
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
                      
file(GLOB SOURCES ${SOURCE_DIR}/*.cpp)
                      
add_library(${MODULE_NAME} STATIC ${SOURCES})
target_include_directories(${MODULE_NAME} PUBLIC ${INCLUDE_DIR})
                      
target_link_libraries(${MODULE_NAME} PUBLIC
                        calendula_compiler_flags
                        calendar_header_w
                        calendar_body_w
                        day_w
                        week_w
                        month_w
                        tree_w
                        managers
                        )

# if(BUILD_TESTS)
#   add_subdirectory(tests)
# endif(BUILD_TESTS)                      
