cmake_minimum_required(VERSION 3.22.1)

project(audio)

add_subdirectory(lame lame)
add_subdirectory(silk silk)

add_library(audio SHARED
        audio/SilkCoder.cpp
        audio/LameCoder.cpp
        audio.cpp
)

target_include_directories(audio PRIVATE .)

target_link_libraries(audio lame silk log)
