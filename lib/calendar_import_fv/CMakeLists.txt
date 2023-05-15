add_library(calendar_import_fv src/calendar_import_fv.cpp)

target_include_directories(calendar_import_fv PUBLIC include)

target_link_libraries(calendar_import_fv PUBLIC
                      calendar_import_fm
                      calendula_compiler_flags)

if(BUILD_TESTS)
  add_subdirectory(tests)
endif(BUILD_TESTS)
