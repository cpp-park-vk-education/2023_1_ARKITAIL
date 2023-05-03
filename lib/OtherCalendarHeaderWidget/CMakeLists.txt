add_library(OtherCalendarHeaderWidget  src/OtherCalendarHeaderWidget.cpp)

target_include_directories(OtherCalendarHeaderWidget  PUBLIC include)

target_link_libraries(OtherCalendarHeaderWidget  PUBLIC
                      CalendarHeaderWidget
                      calendula_compiler_flags)

