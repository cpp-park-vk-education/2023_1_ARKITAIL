add_library(personal_calendar_header_w src/personal_calendar_header_w.cpp)

target_include_directories(personal_calendar_header_w PUBLIC include)

target_link_libraries(personal_calendar_header_w PUBLIC
                      calendar_header_w
                      calendula_compiler_flags)
