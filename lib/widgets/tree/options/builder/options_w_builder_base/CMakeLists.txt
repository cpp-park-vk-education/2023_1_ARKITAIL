add_library(options_w_builder_base  src/options_w_builder_base.cpp)

target_include_directories(options_w_builder_base  PUBLIC include interface)

target_link_libraries(options_w_builder_base  PUBLIC
                      calendula_compiler_flags
                      options_w)
