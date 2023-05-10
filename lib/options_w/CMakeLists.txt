add_library(options_w  src/options_w.cpp)

target_include_directories(options_w  PUBLIC include)

target_link_libraries(options_w  PUBLIC
                      calendula_compiler_flags)
