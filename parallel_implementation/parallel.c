#include "common_functions.h"

static int find_max(const int *array, size_t size) {
  if (!array || size == 0) {
    return -1;
  }
  int max_jump = array[0];
  for (size_t i = 0; i < size; ++i) {
    if (array[i] > max_jump) {
      max_jump = array[i];
    }
  }
  return max_jump;
}

static size_t get_step(size_t size) {
  if (size <= 10) {
    return size;
  }
  size_t counter = 1;
  while (size / 10 > 2) {
    size = size / 10;
    counter *= 10;
  }
  return counter;
}

static size_t get_max_pid(size_t size, size_t step) {
  struct rlimit rlp;
  getrlimit(RLIMIT_NPROC, &rlp);
  size_t max_pid = (size_t)(((double)size + (double)step - 1) / (double)step);
  if (size <= 10) {
    max_pid = 1;
  }
  if (max_pid > rlp.rlim_max) {
    max_pid = rlp.rlim_max;
  }
  return max_pid;
}

static int delegate_work_to_processes(const int *temperatures,
                                      size_t temperature_count, size_t max_pid,
                                      size_t step) {
  int *max_jumps = mmap(NULL, max_pid * sizeof(int), PROT_READ | PROT_WRITE,
                        MAP_SHARED | MAP_ANONYMOUS, -1, 0);

  if (max_jumps == MAP_FAILED) {
    printf("Mapping Failed\n");
    return -1;
  }

  int status;
  size_t counter = 0;
  size_t left_bound = 0;
  size_t right_bound = step;

  while (counter < max_pid) {
    size_t counter_copy = counter;
    size_t left_bound_copy = left_bound;
    size_t right_bound_copy = right_bound;
    ++counter;
    left_bound = right_bound;
    right_bound += step;

    int pid = fork();

    if (pid == 0) {
      max_jumps[counter_copy] = find_max_temperature_jump(
          temperatures, temperature_count, left_bound_copy, right_bound_copy);
      exit(0);
    }
  }

  for (size_t i = 0; i < max_pid; i++) {
    wait(&status);
  }

  int result = find_max(max_jumps, max_pid);
  return result;
}

int work(const vector_t *v) {
  if (!v || !v->temperature_array || v->size == 0) {
    return -1;
  }
  size_t step = get_step(v->size);
  size_t max_pid = get_max_pid(v->size, step);

  int *temperatures = mmap(NULL, v->size * sizeof(int), PROT_READ | PROT_WRITE,
                           MAP_SHARED | MAP_ANONYMOUS, -1, 0);
  memcpy(temperatures, v->temperature_array, v->size * sizeof(int));

  int result = delegate_work_to_processes(temperatures, v->size, max_pid, step);
  return result;
}
