add_library(calendar_export_fv src/calendar_export_fv.cpp)

target_include_directories(calendar_export_fv PUBLIC include)

target_link_libraries(calendar_export_fv PUBLIC
                      calendar_export_fm
                      calendula_compiler_flags)

if(BUILD_TESTS)
  add_subdirectory(tests)
endif(BUILD_TESTS)
