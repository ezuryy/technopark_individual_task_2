#include "common_functions.h"

int work(const vector_t* v) {
  if (!v) {
    return -1;
  }
  int result =
      find_max_temperature_jump(v->temperature_array, v->size, 0, v->size);
  return result;
}
