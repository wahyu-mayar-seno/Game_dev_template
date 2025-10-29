#include "math/linear_algebra.h"

void mat4_ortho(f32 out[16], f32 left, f32 right, f32 bottom, f32 top,
                f32 nearZ, f32 farZ) {
  f32 rl = right - left;
  f32 tb = top - bottom;
  f32 fn = farZ - nearZ;

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
