file(GLOB_RECURSE libsrc *.h *.cpp *.hpp *.c *.cc)

add_library(tasks ${libsrc})

target_link_libraries(tasks PUBLIC common_lib)

set_target_properties(tasks PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)

include(target_warning_support)
set_warning_level(tasks ultra)
