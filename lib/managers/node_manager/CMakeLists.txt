set(MODULE_NAME node_manager)
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
	unmet_deps
	node
)

