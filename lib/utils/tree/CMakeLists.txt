set(MODULE_NAME tree)
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(VIRTUAL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/virtual)

file(GLOB SOURCES ${SOURCE_DIR}/*.cpp)

add_library(${MODULE_NAME} STATIC ${SOURCES})
target_include_directories(${MODULE_NAME} PUBLIC ${INCLUDE_DIR} ${VIRTUAL_DIR})

target_link_libraries(
    ${MODULE_NAME}
    PUBLIC
    managers
    node
    event
)

if(BUILD_TESTS OR BUILD_${MODULE_NAME}_TESTS)
    add_subdirectory(tests)
endif()

