#include <stdio.h>
#include <stdlib.h>

#include "defer.h"

void PushDeferTable(DeferTable *dh, fn func, void *data) {
  if (dh == NULL) {
    fprintf(stderr, "error dh pointer invalid\n");
    exit(-1);
    return;
  }
  if (dh->size >= dh->cap) {
    fprintf(stderr, "defer table out of task slot, error exit\n");
    exit(-1);
    return;
  }
  dh->tasks[dh->size].func = func;
  dh->tasks[dh->size].data = data;
  dh->size += 1;
}
void PopDeferTable(DeferTable *dh) {
  if (!dh) {
    fprintf(stderr, "Error dh is invalid!!!!!!\n");
    return;
  }
  if (dh->size < 1) {
    fprintf(stderr, "Error no task to pop in this table!!\n");
    return;
  }
  dh->size--;
}
void ExecDeferTable(DeferTable *dh) {
  printf("[INFO] : defer is Executing\n");
  if (dh->size < 1) {
    printf("no task to execute\n");
    return;
  }
  while (dh->size > 0) {
    dh->size--;
    dh->tasks[dh->size].func(dh->tasks[dh->size].data);
  }
  dh->size = 0;
}
