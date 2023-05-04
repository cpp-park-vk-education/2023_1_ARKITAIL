add_library(TreeNodeCalendarsDirW  src/TreeNodeCalendarsDirW.cpp)

target_include_directories(TreeNodeCalendarsDirW  PUBLIC include)

target_link_libraries(TreeNodeCalendarsDirW  PUBLIC
                      calendula_compiler_flags
                      TreeNodeDirW
                      OptionsW)
