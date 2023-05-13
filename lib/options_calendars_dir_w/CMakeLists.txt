add_library(options_calendars_dir_w  src/options_calendars_dir_w.cpp)

target_include_directories(options_calendars_dir_w  PUBLIC include)

target_link_libraries(options_calendars_dir_w  PUBLIC
                      calendula_compiler_flags)
