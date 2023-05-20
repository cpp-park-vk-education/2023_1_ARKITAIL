set(MODULE_NAME user_manager)
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

file(GLOB SOURCES ${SOURCE_DIR}/*.cpp)

add_library(${MODULE_NAME} STATIC ${SOURCES})
target_include_directories(${MODULE_NAME} PUBLIC ${INCLUDE_DIR})

target_link_libraries(${MODULE_NAME} PRIVATE
	managers
	user
	db_managers
)

if (BUILD_TESTS)
	add_subdirectory(tests)
endif()

