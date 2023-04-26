add_library(navigation src/navigation.cpp)

target_include_directories(navigation PUBLIC inc)

target_link_libraries(navigation PUBLIC
                    wt
                    calendula_compiler_flags)
