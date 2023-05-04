add_library(PersonalCalendarHeaderW src/PersonalCalendarHeaderW.cpp)

target_include_directories(PersonalCalendarHeaderW PUBLIC include)

target_link_libraries(PersonalCalendarHeaderW PUBLIC
                      CalendarHeaderW
                      AddEventDialog
                      calendula_compiler_flags)

