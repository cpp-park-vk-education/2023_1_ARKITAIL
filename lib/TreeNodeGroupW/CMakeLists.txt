add_library(TreeNodeGroupW  src/TreeNodeGroupW.cpp)

target_include_directories(TreeNodeGroupW  PUBLIC include)

target_link_libraries(TreeNodeGroupW  PUBLIC
                      TreeNodeW
                      OptionsW
                      calendula_compiler_flags)
