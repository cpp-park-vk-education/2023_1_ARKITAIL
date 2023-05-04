add_library(MonthW src/MonthW.cpp)

target_include_directories(MonthW PUBLIC include)

target_link_libraries(MonthW PUBLIC
                      CalendarBodyW
                      EventW
                      calendula_compiler_flags)
