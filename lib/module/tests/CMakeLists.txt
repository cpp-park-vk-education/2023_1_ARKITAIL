project(MyProjectTests)

find_package(Wt REQUIRED)

add_executable(MyProjectTests test_create_table.cpp)

target_link_libraries(MyProjectTests 
                      wt
                      wtdbo
                      wtdbopostgres
                      gtest_main)
                                     

add_test(NAME MyProjectTests COMMAND MyProjectTests)


