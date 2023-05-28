add_library(event_d  src/event_d.cpp)

target_include_directories(event_d  PUBLIC include)

target_link_libraries(event_d  PUBLIC
                      calendula_compiler_flags
                      event
                      session_scope_map
                      comments_container_w)
