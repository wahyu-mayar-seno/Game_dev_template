#include <stdio.h>

#include <miniaudio.h>

#include "defer.h"
#include "type.h"
// defer wrapper
void defer_ma_engine_uninit(void *data) { ma_engine_uninit(data); }
// defer wrapper
i32 main() {
  defer_task _task[10];
  defer_holder table = {.tasks = _task, .size = 0, .cap = 10};
  ma_result result;
  ma_engine engine;
  result = ma_engine_init(NULL, &engine);
  if (result != MA_SUCCESS) {
    printf("failed to init ma_engine");
    goto cleanup;
  }
  push_task(&table, defer_ma_engine_uninit, &engine);

  printf("playing sound\n");
  result =
      ma_engine_play_sound(&engine, "./assets/music/nanatsuNoTaizai.mp3", NULL);
  if (result != MA_SUCCESS) {
    printf("can't play sound\n");
  }
  getchar();
  exec_defer(&table);
  return 0;
cleanup:
  exec_defer(&table);
  return -1;
}
