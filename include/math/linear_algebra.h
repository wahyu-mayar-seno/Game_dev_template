#ifndef MATH_LINEAR_ALGEBRA_H
#define MATH_LINEAR_ALGEBRA_H

#include "type.h"

typedef struct {
  f32 m[16];
} mat4x4;
void mat4_ortho(f32 out[16], f32 left, f32 right, f32 bottom, f32 top,
                f32 nearZ, f32 farZ);

#endif
