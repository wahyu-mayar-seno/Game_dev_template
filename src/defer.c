#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "defer.h"
void push_task(defer_holder *dh, fn func, void *data) {
  if (dh == NULL) {
    fprintf(stderr, "error dh pointer invalid\n");
    exit(-1);
  }
  if (dh->size >= dh->cap) {
    fprintf(stderr, "defer table out of task slot, error exit\n");
    exit(-1);
  }
  dh->tasks[dh->size].func = func;
  dh->tasks[dh->size].data = data;
  dh->size += 1;
}
void pop_task(defer_holder *dh) {
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
void exec_defer(defer_holder *dh) {
  printf("[INFO] : defer is Executing\n");
  while (dh->size > 0) {
    dh->size--;
    dh->tasks[dh->size].func(dh->tasks[dh->size].data);
  }
  dh->size = 0;
}
