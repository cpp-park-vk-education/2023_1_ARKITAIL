set(MODULE_NAME db_mock)
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

file(GLOB SOURCES ${SOURCE_DIR}/*.cpp)

add_library(${MODULE_NAME} STATIC ${SOURCES})
target_include_directories(${MODULE_NAME} PUBLIC ${INCLUDE_DIR})

target_link_libraries(
	${MODULE_NAME}
	PUBLIC
	user
	node
	directory
	calendar
	event
	comment
	tag
	profile
)

# if (BUILD_TESTS)
# 	add_subdirectory(tests)
# endif()

