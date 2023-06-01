add_library(event_w src/EventW.cpp)

target_include_directories(event_w PUBLIC include)

target_link_libraries(event_w PUBLIC
                      calendula_compiler_flags
                      event_d
                      time_utils)

# affeeal: пока закомментил, т.к. у меня не работало...
if(BUILD_TESTS)
  # add_subdirectory(tests)
endif(BUILD_TESTS)   
