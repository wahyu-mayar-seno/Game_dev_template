#include "gmath.h"
void mat4_ortho(float out[16], float left, float right, float bottom, float top,
                float nearZ, float farZ) {
  float rl = right - left;
  float tb = top - bottom;
  float fn = farZ - nearZ;

  out[0] = 2.0f / rl;
  out[1] = 0.0f;
  out[2] = 0.0f;
  out[3] = 0.0f;

  out[4] = 0.0f;
  out[5] = 2.0f / tb;
  out[6] = 0.0f;
  out[7] = 0.0f;

  out[8] = 0.0f;
  out[9] = 0.0f;
  out[10] = -2.0f / fn;
  out[11] = 0.0f;

  out[12] = -(right + left) / rl;
  out[13] = -(top + bottom) / tb;
  out[14] = -(farZ + nearZ) / fn;
  out[15] = 1.0f;
}
