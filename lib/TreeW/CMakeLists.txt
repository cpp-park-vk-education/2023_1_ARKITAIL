add_library(TreeW  src/TreeW.cpp)

target_include_directories(TreeW  PUBLIC include)

target_link_libraries(TreeW  PUBLIC
                      calendula_compiler_flags
                      TreeNodeW)
