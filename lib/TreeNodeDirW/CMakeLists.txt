add_library(TreeNodeDirW  src/TreeNodeDirW.cpp)

target_include_directories(TreeNodeDirW  PUBLIC include)

target_link_libraries(TreeNodeDirW  PUBLIC
                      calendula_compiler_flags
                      TreeNodeW)
