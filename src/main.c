#include <glad/glad.h> // harus duluan!
//
#include <stdio.h>
//
#include <GLFW/glfw3.h>

#include "shader.h"

static void error_callback(int error, const char *description) {
  fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

int main(void) {
  glfwSetErrorCallback(error_callback);
  if (!glfwInit()) {
    fprintf(stderr, "Failed to initialize GLFW\n");
    return -1;
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow *window = glfwCreateWindow(800, 600, "GLAD + GLFW", NULL, NULL);
  if (!window) {
    fprintf(stderr, "Failed to create window\n");
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);

  // 🔹 load OpenGL function pointers via GLAD
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    fprintf(stderr, "Failed to initialize GLAD\n");
    glfwTerminate();
    return -1;
  }

  printf("OpenGL Version: %s\n", glGetString(GL_VERSION));

  float vertices[] = {
      // positions        // colors
      -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // merah
      0.5f,  -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // hijau
      0.0f,  0.5f,  0.0f, 0.0f, 0.0f, 1.0f  // biru
  };

  GLuint vao, vbo;
  glGenVertexArrays(1, &vao);
  glGenBuffers(1, &vbo);

  glBindVertexArray(vao);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  // posisi
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  // warna
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
                        (void *)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  // perbaikan clear color: harus dalam range 0.0 - 1.0
  glClearColor(170.0f / 255.0f, 0.0f, 187.0f / 255.0f, 1.0f);

  Shader shader;
  if (LoadShaderFromFile(&shader, "assets/shader/shader.vs",
                         "assets/shader/shader.fs")) {
    printf("error load shader\n");

    // 🔹 jika shader gagal load, hapus resource VAO dan VBO
    glDeleteVertexArrays(1, &vao); // bersihkan VAO
    glDeleteBuffers(1, &vbo);      // bersihkan VBO

    glfwDestroyWindow(window); // bersihkan window
    glfwTerminate();           // terminate GLFW
    return -1;
  }

  while (!glfwWindowShouldClose(window)) {
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(shader.programId);
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  // 🔹 bersihkan shader
  UnloadShader(&shader);

  // 🔹 bersihkan VAO dan VBO
  glDeleteVertexArrays(1, &vao); // hapus VAO
  glDeleteBuffers(1, &vbo);      // hapus VBO

  // 🔹 bersihkan window dan terminate GLFW
  glfwDestroyWindow(window);
  glfwTerminate();

  return 0;
}
