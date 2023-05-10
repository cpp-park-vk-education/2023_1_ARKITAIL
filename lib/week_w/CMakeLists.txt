add_library(week_w src/week_w.cpp)

target_include_directories(week_w PUBLIC include)

target_link_libraries(week_w PUBLIC
                      calendar_body_w
                      event_w
                      calendula_compiler_flags)
