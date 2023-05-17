set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

file(GLOB SOURCES ${SOURCE_DIR}/*.cpp)

add_library(directory ${SOURCES})
target_include_directories(directory PUBLIC ${INCLUDE_DIR})

