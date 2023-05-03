add_library(CalendarWidget src/CalendarWidget.cpp)

target_include_directories(CalendarWidget PUBLIC include)

target_link_libraries(CalendarWidget PUBLIC
                      CalendarHeaderWidget
                      CalendarBodyWidget
                      DayWidget
                      WeekWidget
                      MonthWidget
                      utils
                      calendula_compiler_flags)
