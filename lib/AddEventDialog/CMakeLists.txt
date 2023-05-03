add_library(AddEventDialog  src/AddEventDialog.cpp)

target_include_directories(AddEventDialog  PUBLIC include)

target_link_libraries(AddEventDialog  PUBLIC
                      calendula_compiler_flags)
