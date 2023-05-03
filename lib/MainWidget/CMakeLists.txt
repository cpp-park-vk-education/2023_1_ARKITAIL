add_library(MainWidget src/MainWidget.cpp)

target_include_directories(MainWidget PUBLIC include)

target_link_libraries(MainWidget PUBLIC
                      CalendarWidget
                      calendula_compiler_flags)

if(BUILD_TESTS)
  add_subdirectory(tests)
endif(BUILD_TESTS)
