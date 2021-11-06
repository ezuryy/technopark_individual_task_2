#include <parallel.h>

int find_max(const int *array, size_t size) {
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

int parallel_process_job(const vector_t *v) {
  if (!v || !v->temperature_array || v->size == 0) {
    return -1;
  }
  struct rlimit rlp;
  getrlimit(RLIMIT_NPROC, &rlp);
  size_t step = 5;
  size_t max_pid = ceil((double)v->size / (double)step);
  if (max_pid > rlp.rlim_max) {
    max_pid = rlp.rlim_max;
  }

  int *temperatures = mmap(NULL, v->size * sizeof(int), PROT_READ | PROT_WRITE,
                           MAP_SHARED | MAP_ANONYMOUS, -1, 0);
  memcpy(temperatures, v->temperature_array, v->size * sizeof(int));
  size_t temperature_count = v->size;

  int *max_jumps = mmap(NULL, max_pid * sizeof(int), PROT_READ | PROT_WRITE,
                        MAP_SHARED | MAP_ANONYMOUS, -1, 0);
  size_t *counter = mmap(NULL, 1 * sizeof(size_t), PROT_READ | PROT_WRITE,
                         MAP_SHARED | MAP_ANONYMOUS, -1, 0);

  size_t *left_bound = mmap(NULL, 1 * sizeof(size_t), PROT_READ | PROT_WRITE,
                            MAP_SHARED | MAP_ANONYMOUS, -1, 0);
  size_t *right_bound = mmap(NULL, 1 * sizeof(size_t), PROT_READ | PROT_WRITE,
                             MAP_SHARED | MAP_ANONYMOUS, -1, 0);
  if (max_jumps == MAP_FAILED || counter == MAP_FAILED ||
      left_bound == MAP_FAILED || right_bound == MAP_FAILED) {
    printf("Mapping Failed\n");
    return 1;
  }

  int status;
  *counter = 0;
  *left_bound = 0;
  *right_bound = step;

  while (*counter < max_pid) {
    size_t counter_copy = *counter;
    size_t left_bound_copy = *left_bound;
    size_t right_bound_copy = *right_bound;
    ++*counter;
    *left_bound = *right_bound;
    *right_bound += step;

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
