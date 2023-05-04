set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

file(GLOB SOURCES ${SOURCE_DIR}/*.cpp)

add_library(tree SHARED ${SOURCES})
target_include_directories(tree PUBLIC ${INCLUDE_DIR})
target_link_libraries(tree PRIVATE node event)

