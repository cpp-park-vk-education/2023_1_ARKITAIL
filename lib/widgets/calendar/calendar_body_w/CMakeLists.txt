add_library(calendar_body_w src/calendar_body_w.cpp)

target_include_directories(calendar_body_w PUBLIC include interface)

target_link_libraries(calendar_body_w PUBLIC
                      calendula_compiler_flags
                      time_utils)
                 