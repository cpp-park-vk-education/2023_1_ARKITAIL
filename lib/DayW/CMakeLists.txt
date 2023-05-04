add_library(DayW src/DayW.cpp)

target_include_directories(DayW PUBLIC include)

target_link_libraries(DayW PUBLIC
                      CalendarBodyW
                      EventW
                      calendula_compiler_flags)
