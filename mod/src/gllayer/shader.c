#include <stdio.h>
#include <stdlib.h>

#include <glad/glad.h>

#include "gllayer/shader.h"

#include "file.h"
#include "misc/type.h"

i32 LoadShaderFromFile(Shader *shader, const char *vertPath,
                       const char *fragPath) {
  if (!shader) {
    return -1;
  }
  // init zero programId mean invalid program because this
  // procedure may fail with some reason it we will change this in end of proces
  // if success
  shader->programId = 0;

  // load shader source
  char *vertSource = readFile(vertPath);
  char *fragSource = readFile(fragPath);
  // checking valid source
  if (!vertSource || !fragSource) {
    free(vertSource);
    free(fragSource);
    fprintf(stderr, "[Shader] Failed to read shader files\n");
    return -1;
  }
  // creating Vertex shader
  GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertShader, 1, (const char *const *)&vertSource, NULL);
  glCompileShader(vertShader);
  // compiling vertex shader
  GLint success;
  // check compile status
  glGetShaderiv(vertShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    char log[512];
    glGetShaderInfoLog(vertShader, sizeof(log), NULL, log);
    fprintf(stderr, "[Vertex Shader Error] %s:\n%s\n", vertPath, log);
    glDeleteShader(vertShader);
    free(vertSource);
    free(fragSource);
    return -1;
  }
  // creating & compiling fragment shader
  GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragShader, 1, (const char *const *)&fragSource, NULL);
  glCompileShader(fragShader);

  // check compile status
  glGetShaderiv(fragShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    char log[512];
    glGetShaderInfoLog(fragShader, sizeof(log), NULL, log);
    fprintf(stderr, "[Fragment Shader Error] %s:\n%s\n", fragPath, log);
    glDeleteShader(vertShader);
    glDeleteShader(fragShader);
    free(vertSource);
    free(fragSource);
    return -1;
  }
  // program & attact shader into program
  GLuint program = glCreateProgram();
  glAttachShader(program, vertShader);
  glAttachShader(program, fragShader);
  glLinkProgram(program);

  // check linking status
  glGetProgramiv(program, GL_LINK_STATUS, &success);
  if (!success) {
    char log[512];
    glGetProgramInfoLog(program, sizeof(log), NULL, log);
    fprintf(stderr, "[Shader Program Link Error]:\n%s\n", log);
    glDeleteShader(vertShader);
    glDeleteShader(fragShader);
    free(vertSource);
    free(fragSource);
    return -1;
  }

  // Bersihkan shader object (sudah linked)
  glDeleteShader(vertShader);
  glDeleteShader(fragShader);
  free(vertSource);
  free(fragSource);

  shader->programId = program;
  printf("load shader success\n");
  return 0;
}
void UseShader(Shader *shader) {
  if (shader && shader->programId) {
    glUseProgram(shader->programId);
  }
}
i32 UnloadShader(Shader *shader) {
  if (!shader) {
    return -1;
  }

  if (shader->programId != 0) {
    glDeleteProgram(shader->programId);
    shader->programId = 0; // reset agar aman
  }

  return 0;
}
