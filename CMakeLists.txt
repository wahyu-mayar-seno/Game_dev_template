cmake_minimum_required(VERSION 3.1...3.9)
project(mgui)
include_directories(mod/include _dependencies/external)

add_subdirectory(_dependencies/glfw)

add_library(glad _dependencies/externalsrc/glad.c)
add_library(miniaudio _dependencies/externalsrc/miniaudio.c)

add_library(shader mod/src/gllayer/shader.c)
add_library(file mod/src/file.c)
add_library(math mod/src/math/linear_algebra.c)
add_library(defer mod/src/defer.c)


set(MY_LIBS m glad glfw miniaudio shader file math defer)

add_executable(game main/src/game.c)
target_link_libraries(game PRIVATE ${MY_LIBS})
target_include_directories(game PRIVATE main/include)

add_executable(miniplayer main/src/miniplayer.c)
target_link_libraries(miniplayer PRIVATE miniaudio defer m)

