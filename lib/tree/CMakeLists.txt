add_library(tree src/tree.cpp)

target_include_directories(tree PUBLIC inc)

target_link_libraries(tree PUBLIC
                    wt
                    public_calendar
                    calendula_compiler_flags)
