#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>

#include "misc/type.h"

typedef struct {
  GLuint programId;
} Shader;
i32 LoadShaderFromFile(Shader *shader, char const *vert, char const *frag);
void UseShader(Shader *shader);
i32 UnloadShader(Shader *shader);

#endif
