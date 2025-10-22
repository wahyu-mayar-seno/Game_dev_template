#ifndef MATH_LINEAR_ALGEBRA_H
#define MATH_LINEAR_ALGEBRA_H
typedef struct {
  float m[16];
} mat4x4;
void mat4_ortho(float out[16], float left, float right, float bottom, float top,
                float nearZ, float farZ);

#endif
