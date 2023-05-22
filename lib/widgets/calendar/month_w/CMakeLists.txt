add_library(month_w src/month_w.cpp)

target_include_directories(month_w PUBLIC include)

target_link_libraries(month_w PUBLIC
                      calendar_body_w
                      event_w
                      calendula_compiler_flags)
