add_executable(OtherP_tests src/OtherP_tests.cpp)

target_link_libraries(OtherP_tests PUBLIC
                      OtherP
                      GTest::gtest_main
                      calendula_compiler_flags)

add_test(OtherP_tests OtherP_tests)
