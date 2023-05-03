add_library(DayWidget src/DayWidget.cpp)

target_include_directories(DayWidget PUBLIC include)

target_link_libraries(DayWidget PUBLIC
                      CalendarBodyWidget
                      EventWidget
                      calendula_compiler_flags)
