set(MODULE_NAME tag_db_manager)
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

file(GLOB SOURCES ${SOURCE_DIR}/*.cpp)

add_library(${MODULE_NAME} STATIC ${SOURCES})
target_include_directories(${MODULE_NAME} PUBLIC ${INCLUDE_DIR})

target_link_libraries(
	${MODULE_NAME}
	PUBLIC
	tag
	db_managers
  db_models
)

# if (BUILD_TESTS)
# 	add_subdirectory(tests)
# endif()

