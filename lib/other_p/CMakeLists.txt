add_library(other_p src/other_p.cpp)

target_include_directories(other_p PUBLIC include)

target_link_libraries(other_p PUBLIC
                      calendar_w
                      page_widget
                      calendula_compiler_flags)

