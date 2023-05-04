add_library(CalendarHeaderW src/CalendarHeaderW.cpp)

target_include_directories(CalendarHeaderW PUBLIC include)

target_link_libraries(CalendarHeaderW PUBLIC
                      utils
                      calendula_compiler_flags)
