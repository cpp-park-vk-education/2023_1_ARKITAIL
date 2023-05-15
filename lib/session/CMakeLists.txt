add_library(session src/session.cpp)

target_include_directories(session PUBLIC include)

target_link_libraries(session PUBLIC
                      wtdbopostgres
                      user
                      calendula_compiler_flags)
