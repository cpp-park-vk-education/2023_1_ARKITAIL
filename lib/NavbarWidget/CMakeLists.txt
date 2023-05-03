add_library(NavbarWidget src/NavbarWidget.cpp)

target_include_directories(NavbarWidget PUBLIC inc)

target_link_libraries(NavbarWidget PUBLIC
                    wt
                    calendula_compiler_flags)
