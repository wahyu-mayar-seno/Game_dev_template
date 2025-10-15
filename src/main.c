#include <glad/glad.h> // harus duluan!

#include <GLFW/glfw3.h>
#include <stdio.h>

#include "gmath.h"
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

  GLFWwindow *window = glfwCreateWindow(1200, 600, "GLAD + GLFW", NULL, NULL);
  if (!window) {
    fprintf(stderr, "Failed to create window\n");
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);

  //  load OpenGL function pointers via GLAD
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    fprintf(stderr, "Failed to initialize GLAD\n");
    glfwTerminate();
    return -1;
  }

  printf("OpenGL Version: %s\n", glGetString(GL_VERSION));

  float vertices[] = {
      // positions        // colors
      -300.0f, 300.0f,  0.0f, 1.0f, 0.0f, 0.0f, // red
      300.0f,  300.0f,  0.0f, 0.0f, 1.0f, 0.0f, // green
      300.0f,  -300.0f, 0.0f, 0.0f, 0.0f, 1.0f, // blue
      -300.0f, -300.0f, 0.0f, 0.0f, 1.0f, 1.0f, // white

  };
  u32 indices[] = {
      0, 1, 2, //
      0, 2, 3, //
  };

  GLuint vao, vbo, ebo;
  glGenVertexArrays(1, &vao);
  glGenBuffers(1, &vbo);
  glGenBuffers(1, &ebo);

  glBindVertexArray(vao);
  // upload vertex attribut
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  // upload ebo data
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
               GL_STATIC_DRAW);

  // posisi
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  // warna
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
                        (void *)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);
  glBindVertexArray(0);

  // perbaikan clear color: harus dalam range 0.0 - 1.0
  Shader shader;
  if (LoadShaderFromFile(&shader, "./assets/shader/shader.vs",
                         "./assets/shader/shader.fs")) {
    printf("error load shader\n");

    //  jika shader gagal load, hapus resource VAO dan VBO
    glDeleteVertexArrays(1, &vao); // bersihkan VAO
    glDeleteBuffers(1, &vbo);      // bersihkan VBO

    glfwDestroyWindow(window); // bersihkan window
    glfwTerminate();           // terminate GLFW
    return -1;
  }
  f32 orto[16];
  mat4_ortho(orto, 0.f, 1200.f, 600.f, 0.f, -1.f, 1.f);
  i32 loc = glGetUniformLocation(shader.programId, "uProj");

  glClearColor(0, 0, 0, 1);
  while (!glfwWindowShouldClose(window)) {
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(shader.programId);
    glUniformMatrix4fv(loc, 1, GL_FALSE, (const GLfloat *)orto);
    glBindVertexArray(vao);
    // glDrawArrays(GL_TRIANGLES, 0, 3);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  //  bersihkan shader
  UnloadShader(&shader);

  //  bersihkan VAO dan VBO
  glDeleteVertexArrays(1, &vao); // hapus VAO
  glDeleteBuffers(1, &vbo);      // hapus VBO

  //  bersihkan window dan terminate GLFW
  glfwDestroyWindow(window);
  glfwTerminate();

  return 0;
}
