add_library(OptionsW  src/OptionsW.cpp)

target_include_directories(OptionsW  PUBLIC include)

target_link_libraries(OptionsW  PUBLIC
                      calendula_compiler_flags)
