add_library(options_personal_calendar_w  src/options_personal_calendar_w.cpp)

target_include_directories(options_personal_calendar_w  PUBLIC include)

target_link_libraries(options_personal_calendar_w  PUBLIC
                      calendula_compiler_flags)
