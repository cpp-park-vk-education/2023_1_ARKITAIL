add_library(tree src/tree.cpp)

target_include_directories(tree PUBLIC inc)

target_link_libraries(tree PUBLIC
                    wt
                    calendula_compiler_flags)
