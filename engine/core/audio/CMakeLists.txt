file(GLOB_RECURSE libsrc *.h *.cpp *.hpp *.c *.cc)

add_library(audio ${libsrc})

target_link_libraries(audio PUBLIC OpenAL)
target_link_libraries(audio PUBLIC stb_vorbis)

set_target_properties(audio PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)

include(target_warning_support)
set_warning_level(audio ultra)
