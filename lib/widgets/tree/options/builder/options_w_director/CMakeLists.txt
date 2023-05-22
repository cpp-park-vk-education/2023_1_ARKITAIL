add_library(options_w_director  src/options_w_director.cpp)

target_include_directories(options_w_director  PUBLIC include)

target_link_libraries(options_w_director  PUBLIC
                      calendula_compiler_flags
                      options_w_builder_base)
