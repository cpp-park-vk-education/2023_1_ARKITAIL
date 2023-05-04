add_library(TreeNodeW  src/TreeNodeW.cpp)

target_include_directories(TreeNodeW  PUBLIC include)

target_link_libraries(TreeNodeW  PUBLIC
                      calendula_compiler_flags)
