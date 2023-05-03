add_library(PersonalCalendarHeaderWidget src/PersonalCalendarHeaderWidget.cpp)

target_include_directories(PersonalCalendarHeaderWidget PUBLIC include)

target_link_libraries(PersonalCalendarHeaderWidget PUBLIC
                      CalendarHeaderWidget
                      AddEventDialog
                      calendula_compiler_flags)

