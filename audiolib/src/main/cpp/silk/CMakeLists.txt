cmake_minimum_required(VERSION 3.22.1)

enable_language(C)

aux_source_directory(silk-v3-decoder/src SILK_SRC)

add_library(silk STATIC ${SILK_SRC})

target_include_directories(silk PUBLIC "silk-v3-decoder/interface")
target_include_directories(silk PUBLIC "silk-v3-decoder/src")

target_compile_definitions(silk PRIVATE "NO_ASM")

set_target_properties(silk PROPERTIES
        C_STANDARD 11
        POSITION_INDEPENDENT_CODE ON
        COMPILE_FLAGS "-w"
)
