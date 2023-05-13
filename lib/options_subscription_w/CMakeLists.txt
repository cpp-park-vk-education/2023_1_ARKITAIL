add_library(options_subscription_w  src/options_subscription_w.cpp)

target_include_directories(options_subscription_w  PUBLIC include)

target_link_libraries(options_subscription_w  PUBLIC
                      calendula_compiler_flags)

