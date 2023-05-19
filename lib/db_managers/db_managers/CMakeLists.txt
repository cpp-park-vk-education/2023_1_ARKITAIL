set(MODULE_NAME db_managers)
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

file(GLOB SOURCES ${SOURCE_DIR}/*.cpp)

add_library(${MODULE_NAME} STATIC ${SOURCES})
target_include_directories(${MODULE_NAME} PUBLIC ${INCLUDE_DIR})

target_link_libraries(
	${MODULE_NAME}
	PUBLIC
	session_scope_map
	user_db_manager
	node_db_manager
	directory_db_manager
	calendar_db_manager
	event_db_manager
	comment_db_manager
	tag_db_manager
	profile_db_manager
)

if (BUILD_TESTS)
	add_subdirectory(tests)
endif()

