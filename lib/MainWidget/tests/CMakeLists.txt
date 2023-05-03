add_executable(MainWidget_tests src/MainWidget_tests.cpp)

target_link_libraries(MainWidget_tests PUBLIC
                      MainWidget
                      GTest::gtest_main
                      calendula_compiler_flags)

add_test(MainWidget_tests MainWidget_tests)
