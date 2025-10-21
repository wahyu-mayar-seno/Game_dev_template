#include <glad/glad.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <GLFW/glfw3.h>

#include "gmath.h"
#include "shader.h"
#include "type.h"

typedef struct {
  f32 x, y, z;
  f32 r, g, b;
  f32 u, v;
} Vertex;
typedef struct {
  Vertex *vertices;
  u32 *indices;
  i32 vert_size;
  i32 vert_cap;
  i32 indic_size;
  i32 indic_cap;
} Mesh;
i32 MeshInit(Mesh *m, i32 vcap, i32 icap) {
  if (m == NULL || vcap < 1 || icap < 1) {
    printf("failed init mesh\n");
    return -1;
  }
  m->vertices = malloc(sizeof(Vertex) * vcap);
  if (!m->vertices) {
    memset(m, 0, sizeof(Mesh));
    printf("error alocate vertices\n");
    return -1;
  }
  m->indices = malloc(sizeof(u32) * icap);
  if (!m->indices) {
    free(m->vertices);
    memset(m, 0, sizeof(Mesh));
    printf("error alocate indices\n");
    return -1;
  }
  m->indic_cap = icap;
  m->vert_cap = vcap;
  m->indic_size = 0;
  m->vert_size = 0;
  return 0;
}
void MeshDelete(Mesh *m) {
  if (m == NULL || m->vertices == NULL || m->indices == NULL) {
    return;
  }
  free(m->vertices);
  free(m->indices);
  memset(m, 0, sizeof(Mesh));
}
typedef struct {
  f32 x, y, w, h;
} Rect;
int pushRect(Mesh *m) { return 0; }
// Callback: ubah viewport saat window di-resize
int window_w = 300;
int window_h = 600;

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  window_w = width;
  window_h = height;
  glViewport(0, 0, width, height);
}

// Fungsi input sederhana
void processInput(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, 1);
}
int main(void) {
  // 1. Inisialisasi GLFW
  if (!glfwInit()) {
    fprintf(stderr, "GLFW init failed!\n");
    return -1;
  }

  // Tentukan versi OpenGL dan profil
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // 2. Buat window
  GLFWwindow *window =
      glfwCreateWindow(window_w, window_h, "GLFW + GLAD (C)", NULL, NULL);
  if (!window) {
    fprintf(stderr, "Failed to create GLFW window!\n");
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  // 3. Load GLAD
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    fprintf(stderr, "Failed to initialize GLAD!\n");
    glfwDestroyWindow(window);
    glfwTerminate();
    return -1;
  }
  Shader shader;
  if (LoadShaderFromFile(&shader, "assets/shader/shader.vs",

                         "assets/shader/shader.fs")) {
    goto cleanup;
  }

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
  glGenVertexArrays(1, &vao);
  glGenBuffers(1, &vbo);
  glGenBuffers(1, &ebo);

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

  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  // 4. Viewport awal
  glViewport(0, 0, window_w, window_h);

  // 5. Loop utama
  glClearColor(1.f, 0.2f, 1.f, 1.0f);
  f32 proj[16];
  mat4_ortho(proj, 0, 300, 300, 0, 0, -1);
  int uprojloc = glGetUniformLocation(shader.programId, "uProj");

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
  glDeleteBuffers(1, &ebo);
  glDeleteBuffers(1, &vbo);
  glDeleteVertexArrays(1, &vao);
  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
  // cleanup main
  glDeleteBuffers(1, &ebo);
  glDeleteBuffers(1, &vbo);
  glDeleteVertexArrays(1, &vao);
  UnloadShader(&shader);
cleanup:
  glfwDestroyWindow(window);
  glfwTerminate();
  return -1;
}
