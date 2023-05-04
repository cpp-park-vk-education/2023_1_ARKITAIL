add_library(OptionsCalendarsDirW  src/OptionsCalendarsDirW.cpp)

target_include_directories(OptionsCalendarsDirW  PUBLIC include)

target_link_libraries(OptionsCalendarsDirW  PUBLIC
                      calendula_compiler_flags
                      OptionsW)
