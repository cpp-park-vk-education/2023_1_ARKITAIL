add_library(CalendarBodyWidget src/CalendarBodyWidget.cpp)

target_include_directories(CalendarBodyWidget PUBLIC include)

target_link_libraries(CalendarBodyWidget PUBLIC
                      calendula_compiler_flags)
