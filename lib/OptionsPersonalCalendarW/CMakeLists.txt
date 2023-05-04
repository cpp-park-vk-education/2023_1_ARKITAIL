add_library(OptionsPersonalCalendarW  src/OptionsPersonalCalendarW.cpp)

target_include_directories(OptionsPersonalCalendarW  PUBLIC include)

target_link_libraries(OptionsPersonalCalendarW  PUBLIC
                      calendula_compiler_flags
                      OptionsW)
