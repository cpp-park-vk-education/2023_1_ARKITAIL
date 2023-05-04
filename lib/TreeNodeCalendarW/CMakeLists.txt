add_library(TreeNodeCalendarW  src/TreeNodeCalendarW.cpp)

target_include_directories(TreeNodeCalendarW  PUBLIC include)

target_link_libraries(TreeNodeCalendarW  PUBLIC
                      calendula_compiler_flags
                      TreeNodeW
                      OptionsW)
