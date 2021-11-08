#ifndef TEST_PROCESSES_PARALLEL_H
#define TEST_PROCESSES_PARALLEL_H

#include <common_functions.h>
#include <string.h>
#include <sys/resource.h>

int find_max(const int* array, size_t size);

int delegate_work_to_processes(const int *temperatures, size_t temperature_count, size_t max_pid, size_t step);

int work(const vector_t* v);

#endif  // TEST_PROCESSES_PARALLEL_H
