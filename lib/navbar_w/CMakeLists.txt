add_library(navbar_w src/navbar_w.cpp)

target_include_directories(navbar_w PUBLIC inc)

target_link_libraries(navbar_w PUBLIC
                    wt
                    calendula_compiler_flags)
 
