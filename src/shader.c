#include <glad/glad.h>
#include <stdio.h>
#include <stdlib.h>

#include "shader.h"
#include "type.h"
static char *readFile(const char *path) {
  FILE *file = fopen(path, "rb");
  if (!file) {
    return NULL;
  }

  fseek(file, 0, SEEK_END);
  long len = ftell(file);
  rewind(file);

  char *buf = (char *)malloc(len + 1);
  if (!buf) {
    fclose(file);
    return NULL;
  }

  fread(buf, 1, len, file);
  buf[len] = '\0';
  fclose(file);
  return buf;
}

i32 LoadShaderFromFile(Shader *shader, const char *vertPath,
                       const char *fragPath) {
  if (!shader) {
    return -1;
  }

  char *vertSource = readFile(vertPath);
  char *fragSource = readFile(fragPath);

  if (!vertSource || !fragSource) {
    free(vertSource);
    free(fragSource);
    fprintf(stderr, "[Shader] Failed to read shader files\n");
    return -1;
  }

  GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertShader, 1, (const char *const *)&vertSource, NULL);
  glCompileShader(vertShader);

  GLint success;
  glGetShaderiv(vertShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    char log[512];
    glGetShaderInfoLog(vertShader, sizeof(log), NULL, log);
    fprintf(stderr, "[Vertex Shader Error] %s:\n%s\n", vertPath, log);
    free(vertSource);
    free(fragSource);
    return -1;
  }

  GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragShader, 1, (const char *const *)&fragSource, NULL);
  glCompileShader(fragShader);

  glGetShaderiv(fragShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    char log[512];
    glGetShaderInfoLog(fragShader, sizeof(log), NULL, log);
    fprintf(stderr, "[Fragment Shader Error] %s:\n%s\n", fragPath, log);
    glDeleteShader(vertShader);
    free(vertSource);
    free(fragSource);
    return -1;
  }

  GLuint program = glCreateProgram();
  glAttachShader(program, vertShader);
  glAttachShader(program, fragShader);
  glLinkProgram(program);

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
