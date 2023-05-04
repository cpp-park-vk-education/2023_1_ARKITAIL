add_library(OptionsSubscriptionW  src/OptionsSubscriptionW.cpp)

target_include_directories(OptionsSubscriptionW  PUBLIC include)

target_link_libraries(OptionsSubscriptionW  PUBLIC
                      calendula_compiler_flags
                      OptionsW)
