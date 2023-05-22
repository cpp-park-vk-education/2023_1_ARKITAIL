add_library(event_w src/event_w.cpp)

target_include_directories(event_w PUBLIC include)

target_link_libraries(event_w PUBLIC
                      calendula_compiler_flags
                      event_d
                      time_utils)
