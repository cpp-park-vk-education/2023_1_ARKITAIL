add_executable(${MODULE_NAME}_tests tests.cpp)

target_link_libraries(${MODULE_NAME}_tests PRIVATE ${MODULE_NAME} GTest::gtest_main)

add_test(${MODULE_NAME}_tests ${MODULE_NAME}_tests)
