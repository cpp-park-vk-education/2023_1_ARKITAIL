add_library(NavbarW src/NavbarW.cpp)

target_include_directories(NavbarW PUBLIC inc)

target_link_libraries(NavbarW PUBLIC
                    wt
                    calendula_compiler_flags)
