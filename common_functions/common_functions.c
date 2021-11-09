#include <common_functions.h>

bool create_vector(vector_t* v) {
  if (!v) {
    return false;
  }
  v->capacity = 1;
  v->size = 0;
  v->temperature_array = (int*)malloc(1 * sizeof(int));
  if (!v->temperature_array) {
    return false;
  }
  return true;
}

bool push_back(vector_t* v, int element) {
  if (!v || !v->temperature_array) {
    return false;
  }
  if (v->capacity == v->size) {
    v->capacity = 2 * v->capacity;
    v->temperature_array =
        (int*)realloc(v->temperature_array, v->capacity * sizeof(int));
    if (!v->temperature_array) {
      return false;
    }
  }
  v->temperature_array[v->size] = element;
  ++v->size;
  return true;
}

bool delete_vector(vector_t* v) {
  if (!v || !v->temperature_array) {
    return false;
  }
  free(v->temperature_array);
  return true;
}

bool read_vector(vector_t* v, FILE* in) {
  if (!v || !in) {
    return false;
  }
  int MAX_DIGIT_SIZE = 10;
  char count[MAX_DIGIT_SIZE];
  fgets(count, MAX_DIGIT_SIZE, in);
  size_t _count = (size_t)strtol(count, NULL, 10);
  char number[MAX_DIGIT_SIZE];
  for (size_t i = 0; i < _count; ++i) {
    fgets(number, MAX_DIGIT_SIZE, in);
    int _number = (int)strtol(number, NULL, 10);
    if (!push_back(v, _number)) {
      return false;
    }
  }
  return true;
}

int find_max_temperature_jump(const int* temps, size_t size, size_t left_bound,
                              size_t right_bound) {
  if (!temps || size <= left_bound) {
    return -1;
  }
  int max_jump = -1;
  if (left_bound > 0) {
    max_jump = temps[left_bound] - temps[left_bound - 1];
  }
  for (size_t i = left_bound; i + 1 < right_bound && i + 1 < size; ++i) {
    if (temps[i + 1] - temps[i] > max_jump) {
      max_jump = temps[i + 1] - temps[i];
    }
  }
  return max_jump;
}
