cmake_minimum_required(VERSION 3.22.1)

enable_language(C)

aux_source_directory(lame-3.100/libmp3lame LAME_SRC)
aux_source_directory(lame-3.100/mpglib LAME_SRC)

add_library(lame STATIC ${LAME_SRC})

target_include_directories(lame PUBLIC "lame-3.100/include")
target_include_directories(lame PUBLIC "lame-3.100/libmp3lame")
target_include_directories(lame PUBLIC "lame-3.100/mpglib")

set_target_properties(lame PROPERTIES
        C_STANDARD 11
        POSITION_INDEPENDENT_CODE ON
        COMPILE_FLAGS "-w"
)
