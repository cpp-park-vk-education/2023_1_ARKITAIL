add_executable(user_tests src/user_tests.cpp)

target_link_libraries(user_tests PUBLIC
                      user
                      GTest::gtest_main
                      calendula_compiler_flags)

add_test(user_tests user_tests)
