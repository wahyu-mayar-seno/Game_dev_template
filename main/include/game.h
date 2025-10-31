#ifndef GAME_H
#define GAME_H
#include <GLFW/glfw3.h>

#include "misc/type.h"

typedef struct {
  GLFWwindow *window;
  i32 windowWidth;
  i32 windowHeight;
  i32 isRuning;

} _state;

extern _state global;

i32 InitGame();
void UpdateGame();
void UninitGame();
#endif
