add_library(EventW src/EventW.cpp)

target_include_directories(EventW PUBLIC include)

target_link_libraries(EventW PUBLIC
                      CalendarBodyW
                      calendula_compiler_flags)
