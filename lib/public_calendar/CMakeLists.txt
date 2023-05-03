add_library(public_calendar src/public_calendar.cpp)

target_include_directories(public_calendar PUBLIC inc)

target_link_libraries(public_calendar PUBLIC
                    calendar
                    tree
                    wt
                    calendula_compiler_flags)
