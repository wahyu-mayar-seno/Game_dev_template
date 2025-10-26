#ifndef DEFER_H
#define DEFER_H

#include "type.h"

typedef void (*fn)(void *);
typedef struct {
  fn func;
  void *data;
} defer_task;

typedef struct {
  defer_task *tasks;
  i32 cap;
  i32 size;
} defer_holder;

// push task i32o table if there's a slot
void push_task(defer_holder *dh, fn func, void *data);
// remove task in the last slot( basicaly just size-=1)
void pop_task(defer_holder *dh);
/* this func will run all task in order LIFO(Last In First Out) this func mush
 called in the end of scope*/
void exec_defer(defer_holder *dh);
#endif
