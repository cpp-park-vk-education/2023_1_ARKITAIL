add_library(calendula_application src/calendula_application.cpp)

target_include_directories(calendula_application PUBLIC include)

target_link_libraries(calendula_application PUBLIC
                      session
                      utils
                      calendula_compiler_flags)
