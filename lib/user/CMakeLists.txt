add_library(user src/user.cpp)

target_include_directories(user PUBLIC include)

target_link_libraries(user PUBLIC
                      wt
                      wtdbo
                      calendula_compiler_flags)

if(BUILD_TESTS)
  add_subdirectory(tests)
endif(BUILD_TESTS)
