add_library(calendar_header_w src/calendar_header_w.cpp)

target_include_directories(calendar_header_w PUBLIC include interface)

target_link_libraries(calendar_header_w PUBLIC
                      calendar_body_w
                      calendar_w
                      calendula_compiler_flags)

if(BUILD_TESTS)
  add_subdirectory(tests)
endif(BUILD_TESTS)                    
