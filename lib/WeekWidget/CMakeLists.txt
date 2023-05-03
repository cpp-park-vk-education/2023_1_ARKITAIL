add_library(WeekWidget src/WeekWidget.cpp)

target_include_directories(WeekWidget PUBLIC include)

target_link_libraries(WeekWidget PUBLIC
                      CalendarBodyWidget
                      EventWidget
                      calendula_compiler_flags)
