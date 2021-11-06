#include <consistent.h>

int consistent_job(const vector_t* v) {
  int result =
      find_max_temperature_jump(v->temperature_array, v->size, 0, v->size);
  return result;
}
