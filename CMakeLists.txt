cmake_minimum_required(VERSION 3.1...3.9)
project(mgui)
include_directories(include external)

add_subdirectory(dep/glfw)

add_library(glad externalsrc/glad.c)
add_library(miniaudio externalsrc/miniaudio.c)

add_library(shader src/gllayer/shader.c)
add_library(file src/file.c)
add_library(math src/math/linear_algebra.c)
add_library(defer src/defer.c)

set(MY_LIBS m glad glfw miniaudio shader file math defer)

add_executable(mgui src/main.c)
target_link_libraries(mgui PRIVATE ${MY_LIBS})
add_executable(miniplayer miniplayer/main.c)
target_link_libraries(miniplayer PRIVATE miniaudio defer m)

