add_library(EventWidget src/EventWidget.cpp)

target_include_directories(EventWidget PUBLIC include)

target_link_libraries(EventWidget PUBLIC
                      CalendarBodyWidget
                      calendula_compiler_flags)
