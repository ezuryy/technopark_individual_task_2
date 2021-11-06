#ifndef TEST_PROCESSES_PARALLEL_H
#define TEST_PROCESSES_PARALLEL_H

#include <common_functions.h>
#include <libc.h>
#include <sys/resource.h>

int find_max(const int* array, size_t size);

int parallel_process_job(const vector_t* v);

#endif  // TEST_PROCESSES_PARALLEL_H
