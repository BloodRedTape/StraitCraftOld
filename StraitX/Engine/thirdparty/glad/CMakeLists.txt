cmake_minimum_required(VERSION 3.10)

project(glad-loader LANGUAGES C)

set(SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/sources/glad.c
)

add_library(glad ${SOURCES})
target_include_directories(glad PUBLIC include/)
