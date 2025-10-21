#ifndef GMATH_H
#define GMATH_H
typedef struct {
  float m[16];
} mat4x4;
void mat4_ortho(float out[16], float left, float right, float bottom, float top,
                float nearZ, float farZ);

#endif
