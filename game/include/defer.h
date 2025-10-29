#ifndef DEFER_H
#define DEFER_H

#include "misc/type.h"

typedef void (*fn)(void *);
typedef struct {
  fn func;
  void *data;
} DeferTask;

typedef struct {
  DeferTask *tasks;
  i32 cap;
  i32 size;
} DeferTable;

// push task i32o table if there's a slot
void PushDeferTable(DeferTable *dh, fn func, void *data);
// remove task in the last slot( basicaly just size-=1)
void PopDeferTable(DeferTable *dh);
/* this func will run all task in order LIFO(Last In First Out) this func mush
 called in the end of scope*/
void ExecDeferTable(DeferTable *dh);
#endif
