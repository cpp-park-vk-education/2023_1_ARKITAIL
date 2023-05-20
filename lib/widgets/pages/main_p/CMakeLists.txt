add_library(main_p src/main_p.cpp)

target_include_directories(main_p PUBLIC include)

target_link_libraries(main_p PUBLIC
                      calendar_w
                      calendar_body_w
                      personal_calendar_header_w
                      day_w
                      week_w
                      month_w
                      calendula_compiler_flags)

