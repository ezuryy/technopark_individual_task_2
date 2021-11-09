#ifndef TEST_PROCESSES_COMMON_FUNCTIONS_H
#define TEST_PROCESSES_COMMON_FUNCTIONS_H

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/resource.h>
#include <sys/wait.h>
#include <unistd.h>

typedef struct Vector {
  size_t capacity;
  size_t size;
  int* temperature_array;
} vector_t;

bool create_vector(vector_t* v);

bool push_back(vector_t* v, int element);

bool delete_vector(vector_t* v);

bool read_vector(vector_t* v, FILE* in);

int work(const vector_t* v);

int find_max_temperature_jump(const int* temps, size_t size, size_t left_bound,
                              size_t right_bound);

#endif  // TEST_PROCESSES_COMMON_FUNCTIONS_H
