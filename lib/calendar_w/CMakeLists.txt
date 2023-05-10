add_library(calendar_w src/calendar_w.cpp)

target_include_directories(calendar_w PUBLIC include)

target_link_libraries(calendar_w PUBLIC
                      calendar_header_w
                      calendar_body_w
                      day_w
                      week_w
                      month_w
                      tree_w
                      utils
                      calendula_compiler_flags)
if(BUILD_TESTS)
  add_subdirectory(tests)
endif(BUILD_TESTS)                      
