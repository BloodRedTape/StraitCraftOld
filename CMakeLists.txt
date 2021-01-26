cmake_minimum_required(VERSION 3.10)

project(StraitCraft)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/StraitX/Engine)

set(SANDBOX_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/sources/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/sources/straitcraft.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/sources/texture_atlas.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/sources/graphics_pipeline.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/sources/camera.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/sources/math.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/sources/renderer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/sources/block_renderer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/sources/chunk_renderer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/sources/blocks.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/sources/world.cpp   
    ${CMAKE_CURRENT_SOURCE_DIR}/sources/stb_image.c
)

set(SANDBOX_INCLUDES
    ${CMAKE_CURRENT_SOURCE_DIR}/StraitX/Engine/sources
    ${CMAKE_CURRENT_SOURCE_DIR}/sources
)

add_executable(StraitCraft ${SANDBOX_SOURCES})
target_include_directories(StraitCraft PUBLIC ${SANDBOX_INCLUDES})
target_link_libraries(StraitCraft StraitX sfml-system)
