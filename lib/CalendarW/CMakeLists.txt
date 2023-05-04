add_library(CalendarW src/CalendarW.cpp)

target_include_directories(CalendarW PUBLIC include)

target_link_libraries(CalendarW PUBLIC
                      CalendarHeaderW
                      CalendarBodyW
                      DayW
                      WeekW
                      MonthW
                      TreeW
                      utils
                      calendula_compiler_flags)
