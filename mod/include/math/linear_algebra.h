#ifndef MATH_LINEAR_ALGEBRA_H
#define MATH_LINEAR_ALGEBRA_H

#include "misc/type.h"

typedef struct {
  f32 m[16];
} mat4x4;
typedef struct {
  f32 x, y;
} v2;
typedef struct {
  f32 x, y, z;
} v3;
typedef struct {
  f32 x, y, z, w;
} v4;
void mat4_ortho(f32 out[16], f32 left, f32 right, f32 bottom, f32 top,
                f32 nearZ, f32 farZ);
v2 Lerpv2(v2 a, v2 b, f32 t);
v3 Lerpv3(v3 a, v3 b, f32 t);
v4 Lerpv4(v4 a, v4 b, f32 t);

#endif
