add_library(time_utils src/time_utils.cpp)

target_include_directories(time_utils PUBLIC include)

target_link_libraries(time_utils PUBLIC
                      calendula_compiler_flags)
