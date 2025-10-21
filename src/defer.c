#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct {
  void (*fn)(void *);
  void *data;
} defer_task;
typedef struct {
  defer_task *tasks;
  int cap;
  int size;
} defer_holder;
void push_task(defer_holder *dh, void (*fn)(void *), void *data) {
  if (dh == NULL) {
    fprintf(stderr, "error dh pointer invalid\n");
    exit(-1);
  }
  if (dh->size >= dh->cap) {
    fprintf(stderr, "defer table out of task slot, error exit\n");
    exit(-1);
  }
  dh->tasks[dh->size].fn = fn;
  dh->tasks[dh->size].data = data;
  dh->size += 1;
}
void pop_task(defer_holder *dh) {
  if (!dh) {
    fprintf(stderr, "Error dh is invalid!!!!!!\n");
    return;
  }
  if (dh->size < 1) {
    fprintf(stderr, "Error no task to pop ini this table!!\n");
    return;
  }
  dh->size--;
}
int main() {
  defer_task dtask[10];
  memset(dtask, 0, sizeof(dtask));
  defer_holder dtable = {.tasks = dtask, .cap = 3, .size = 0};
  void *mem = malloc(1024);

  void *mem2 = malloc(1024);
  push_task(&dtable, free, mem);
  push_task(&dtable, free, mem2);
  // pseudo call
  // push_task(dtask,foo,foodat);
  printf("program exit\n");
  return 0;
}
