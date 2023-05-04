add_executable(MainP_tests src/MainP_tests.cpp)

target_link_libraries(MainP_tests PUBLIC
                      MainP
                      GTest::gtest_main
                      calendula_compiler_flags)

add_test(MainP_tests MainP_tests)
