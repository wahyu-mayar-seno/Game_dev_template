#ifndef SHADER_H
#define SHADER_H

#include "type.h"

#include <glad/glad.h>
typedef struct {
  GLuint programId;
} Shader;
i32 LoadShaderFromFile(Shader *shader, char const *vert, char const *frag);
i32 UnloadShader(Shader *shader);

#endif
