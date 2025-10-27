#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "type.h"

typedef struct {
  f32 x, y, z;
  f32 r, g, b;
} Vertex;

typedef struct {
  Vertex *vertices;
  u32 *indices;
  i32 vert_size;
  i32 vert_cap;
  i32 indic_size;
  i32 indic_cap;
} Mesh;

i32 MeshInit(Mesh *m, i32 vcap, i32 icap) {
  if (m == NULL || vcap < 1 || icap < 1) {
    printf("failed init mesh\n");
    return -1;
  }
  m->vertices = malloc(sizeof(Vertex) * vcap);
  if (!m->vertices) {
    memset(m, 0, sizeof(Mesh));
    printf("error alocate vertices\n");
    return -1;
  }
  m->indices = malloc(sizeof(u32) * icap);
  if (!m->indices) {
    free(m->vertices);
    memset(m, 0, sizeof(Mesh));
    printf("error alocate indices\n");
    return -1;
  }
  m->indic_cap = icap;
  m->vert_cap = vcap;
  m->indic_size = 0;
  m->vert_size = 0;
  return 0;
}

void MeshDelete(Mesh *m) {
  if (m == NULL || m->vertices == NULL || m->indices == NULL) {
    return;
  }
  free(m->vertices);
  free(m->indices);
  memset(m, 0, sizeof(Mesh));
}
