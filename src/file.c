#include "file.h"

#include <stdio.h>
#include <stdlib.h>
char *readFile(const char *path) {
  FILE *file = fopen(path, "rb");
  if (!file) {
    return NULL;
  }

  fseek(file, 0, SEEK_END);
  long len = ftell(file);
  rewind(file);

  char *buf = (char *)malloc(len + 1);
  if (!buf) {
    fclose(file);
    return NULL;
  }

  fread(buf, 1, len, file);
  buf[len] = '\0';
  fclose(file);
  return buf;
}
