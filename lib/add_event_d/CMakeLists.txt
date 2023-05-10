add_library(add_event_d  src/add_event_d.cpp)

target_include_directories(add_event_d  PUBLIC include)

target_link_libraries(add_event_d  PUBLIC
                      calendula_compiler_flags)

