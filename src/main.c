#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <glad/glad.h>

#include <GLFW/glfw3.h>

#include "math/linear_algebra.h"

#include "gllayer/shader.h"

#include "defer.h"
#include "type.h"

// window re-size callback
i32 window_w = 800;
i32 window_h = 600;
void framebuffer_size_callback(GLFWwindow *window, i32 width, i32 height) {
  window_w = width;
  window_h = height;
  glViewport(0, 0, width, height);
}

// simple input func
void processInput(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, 1);
}

// wrapper for defer
void defer_glfwTerminate(void *data) {
  printf("[INFO] : glfw Terminated\n");
  glfwTerminate();
}
void defer_glfwDestroyWindow(void *data) {
  printf("[INFO] : window Destroyed\n");
  glfwDestroyWindow((GLFWwindow *)data);
}
void defer_UnloadShader(void *data) {
  printf("[INFO] : shader Unloaded\n");
  UnloadShader((Shader *)data);
}
void defer_glDeleteBuffer(void *data) {
  printf("[INFO] : gl buffer Deleted\n");
  printf("pointer of data : %p\n", data);
  glDeleteBuffers(1, (u32 *)data);
}
void defer_glDeleteVertexArrays(void *data) {
  printf("[INFO] : gl VertexArrays Deleted\n");
  printf("pointer of data : %p\n", data);
  glDeleteVertexArrays(1, (u32 *)data);
}
// end of defer_wrapper;
int power(int base, int exp) {
  if (exp < 1) {
    return 1;
  }
  if (exp < 2) {
    return base;
  }
  int res = base;
  for (int i = 1; i < exp; i++) {
    res = res * base;
  }
  return res;
}
// main
i32 main(void) {
  defer_task dtask[10];
  memset(dtask, 0, sizeof(dtask));
  defer_holder dtable = {.tasks = dtask, .cap = 10, .size = 0};
  for (int i = 0; i <= 28; i++) {
    printf("2^%d=%d\n", i, power(2, i));
  }

  // 1. Initializing GLFW
  if (!glfwInit()) {
    printf("[ERROR] : GLFW init failed!\n");
    goto cleanup;
  }
  push_task(&dtable, defer_glfwTerminate, 0);
  // Determine OpenGL Version and  Profil
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // 2. Creating window
  GLFWwindow *window =
      glfwCreateWindow(window_w, window_h, "GLFW + GLAD (C)", NULL, NULL);
  if (!window) {
    printf("Failed to create GLFW window!\n");
    goto cleanup;
  }
  push_task(&dtable, defer_glfwDestroyWindow, window);

  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  // 3. Load GLAD
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    printf("Failed to initialize GLAD!\n");
    goto cleanup;
  }

  Shader shader;
  if (LoadShaderFromFile(&shader, "assets/shader/shader.vs",
                         "assets/shader/shader.fs")) {
    goto cleanup;
  }
  push_task(&dtable, defer_UnloadShader, &shader);

  f32 vertices[] = {
      0,   0,   0, 1, 1, 1, //
      100, 0,   0, 0, 0, 1, //
      100, 100, 0, 0, 1, 0, //
      0,   100, 0, 1, 0, 0, //
  };
  u32 indices[] = {
      0, 1, 2, //
      0, 2, 3  //
  };

  u32 vao, vbo, ebo;
  printf("pointer of vao,vbo,ebo %p, %p,%p\n", &vao, &vbo, &ebo);
  glGenVertexArrays(1, &vao);
  glGenBuffers(1, &vbo);
  glGenBuffers(1, &ebo);

  push_task(&dtable, defer_glDeleteVertexArrays, &vao);
  push_task(&dtable, defer_glDeleteBuffer, &vbo);
  push_task(&dtable, defer_glDeleteBuffer, &ebo);

  glBindVertexArray(vao);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
               GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(f32) * 6, 0);
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(f32) * 6,
                        (void *)(sizeof(f32) * 3));
  glEnableVertexAttribArray(1);
  // unbind ing vao vbo ebo
  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

  // 4. Intial Viewport
  glViewport(0, 0, window_w, window_h);

  glClearColor(1.f, 0.2f, 1.f, 1.0f);

  f32 proj[16];
  mat4_ortho(proj, 0, 300, 300, 0, 0, -1);
  i32 uprojloc = glGetUniformLocation(shader.programId, "uProj");

  // 5. Main Loop
  while (!glfwWindowShouldClose(window)) {

    processInput(window);
    // Clear layar dengan warna biru tua

    mat4_ortho(proj, 0, window_w, window_h, 0, 0, -1);
    glClear(GL_COLOR_BUFFER_BIT);

    UseShader(&shader);
    glUniformMatrix4fv(uprojloc, 1, GL_FALSE, proj);
    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  // 6. Bersihkan
  printf("[INFO] : exited normaly\n");
  exec_defer(&dtable);
  return 0;
cleanup:
  printf("[ERROR] : exited abnormaly\n");
  exec_defer(&dtable);
  return -1;
}
