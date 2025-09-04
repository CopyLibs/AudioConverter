cmake_minimum_required(VERSION 3.22.1)

project(audio)

add_subdirectory(lame lame)

add_library(audio SHARED
        audio.cpp
)

target_link_libraries(audio lame log)