add_library(CalendarBodyW src/CalendarBodyW.cpp)

target_include_directories(CalendarBodyW PUBLIC include)

target_link_libraries(CalendarBodyW PUBLIC
                      calendula_compiler_flags)
