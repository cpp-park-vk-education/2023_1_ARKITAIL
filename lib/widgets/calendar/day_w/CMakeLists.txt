add_library(day_w src/day_w.cpp)

target_include_directories(day_w PUBLIC include)

target_link_libraries(day_w PUBLIC
                      calendar_body_w
                      event_w
                      calendula_compiler_flags)
