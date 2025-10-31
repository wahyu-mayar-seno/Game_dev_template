#include <stdio.h>
#include <string.h>

#include <glad/glad.h>

#include <GLFW/glfw3.h>

#include "defer.h"
#include "game.h"
_state global;
int main(void) {
  if (InitGame()) {
    printf("init failed\n");
    return -1;
  }
  UpdateGame();
  UninitGame();
  return 0;
}
i32 InitGame() {
  DeferTask _task[10];
  memset(_task, 0, sizeof(_task));
  DeferTable table = {.tasks = _task, .cap = 10, .size = 0};

  if (glfwInit()) {
    printf("failed init glfw\n");
    goto clean_up;
  }
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  return 0;
clean_up:
  ExecDeferTable(&table);
  return -1;
}
void UpdateGame() {}
void UninitGame() {}
