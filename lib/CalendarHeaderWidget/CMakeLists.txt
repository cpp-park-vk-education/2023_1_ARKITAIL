add_library(CalendarHeaderWidget src/CalendarHeaderWidget.cpp)

target_include_directories(CalendarHeaderWidget PUBLIC include)

target_link_libraries(CalendarHeaderWidget PUBLIC
                      utils
                      calendula_compiler_flags)
