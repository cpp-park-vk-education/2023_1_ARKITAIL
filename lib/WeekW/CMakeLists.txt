add_library(WeekW src/WeekW.cpp)

target_include_directories(WeekW PUBLIC include)

target_link_libraries(WeekW PUBLIC
                      CalendarBodyW
                      EventW
                      calendula_compiler_flags)
