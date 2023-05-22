add_library(options_w_builder  src/options_w_builder.cpp)

target_include_directories(options_w_builder  PUBLIC include)

target_link_libraries(options_w_builder  PUBLIC
                      calendula_compiler_flags
                      options_w
                      options_w_builder_base)
