cmake_minimum_required(VERSION 3.1...3.9)
project(waveform)
include_directories(include external)

add_subdirectory(dep/glfw)

add_library(glad externalsrc/glad.c)
add_library(miniaudio externalsrc/miniaudio.c)
add_library(shader src/shader.c)

set(WAVELIB glad glfw miniaudio shader)
add_executable(waveform src/main.c)
target_link_libraries(waveform PRIVATE ${WAVELIB})
