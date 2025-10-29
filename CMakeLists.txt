cmake_minimum_required(VERSION 3.1...3.9)
project(mgui)
include_directories(game/include dependencies/external)

add_subdirectory(dependencies/glfw)

add_library(glad dependencies/externalsrc/glad.c)
add_library(miniaudio dependencies/externalsrc/miniaudio.c)

add_library(shader game/src/gllayer/shader.c)
add_library(file game/src/file.c)
add_library(math game/src/math/linear_algebra.c)
add_library(defer game/src/defer.c)


set(MY_LIBS m glad glfw miniaudio shader file math defer)

add_executable(game game/main/game.c)
target_link_libraries(game PRIVATE ${MY_LIBS})

add_executable(miniplayer game/main/miniplayer.c)
target_link_libraries(miniplayer PRIVATE miniaudio defer m)

