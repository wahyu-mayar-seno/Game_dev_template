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

v2 Lerpv2(v2 a, v2 b, f32 t) {
  return (v2){
      .x = a.x + (b.x - a.x) * t, //
      .y = a.y + (b.y - a.y) * t, //
  };
}
v3 Lerpv3(v3 a, v3 b, f32 t) {
  return (v3){
      .x = a.x + (b.x - a.x) * t, //
      .y = a.y + (b.y - a.y) * t, //
      .z = a.z + (b.z - a.z) * t, //
  };
}
v4 Lerpv4(v4 a, v4 b, f32 t) {
  return (v4){
      .x = a.x + (b.x - a.x) * t, //
      .y = a.y + (b.y - a.y) * t, //
      .z = a.z + (b.z - a.z) * t, //
      .w = a.w + (b.w - a.w) * t, //
  };
}
