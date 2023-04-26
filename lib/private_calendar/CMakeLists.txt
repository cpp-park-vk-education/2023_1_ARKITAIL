add_library(private_calendar src/private_calendar.cpp)

target_include_directories(private_calendar PUBLIC inc)

target_link_libraries(private_calendar PUBLIC
                    calendar
                    tree
                    wt
                    calendula_compiler_flags)
