add_library(MonthWidget src/MonthWidget.cpp)

target_include_directories(MonthWidget PUBLIC include)

target_link_libraries(MonthWidget PUBLIC
                      CalendarBodyWidget
                      EventWidget
                      calendula_compiler_flags)
