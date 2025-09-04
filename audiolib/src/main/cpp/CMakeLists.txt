cmake_minimum_required(VERSION 3.22.1)

project(audio)

add_library(audio SHARED
        audio.cpp
)

target_link_libraries(audio log)