#include <getopt.h>
#include <time.h>

#include "common_functions.h"

int main(int argc, char *argv[]) {
  int opt;
  char *opts = "i:o:h";
  char *input = NULL;
  char *output = NULL;

  while ((opt = getopt(argc, argv, opts)) != -1) {
    switch (opt) {
      case 'i':
        input = malloc((strlen(optarg) + 1) * sizeof(char));
        strcpy(input, optarg);
        break;
      case 'o':
        output = malloc((strlen(optarg) + 1) * sizeof(char));
        strcpy(output, optarg);
        break;
      case 'h':
        printf("Usage: %s [-h|-i|-o] <args>\n", argv[0]);
        break;
      default:
        break;
    }
  }
  vector_t v;
  if (!create_vector(&v)) {
    printf("Creating vector failed\n");
    return 1;
  }
  if (!input) {
    if (!read_vector(&v, stdin)) {
      printf("Reading vector failed\n");
      return 1;
    }
  } else {
    FILE *file = fopen(input, "r");

    if (!file) {
      printf("Opening file failed\n");
      return 1;
    }

    if (!read_vector(&v, file)) {
      printf("Reading vector failed\n");
      return 1;
    }

    if (fclose(file)) {
      printf("Closing file failed\n");
      return 1;
    }
  }
  size_t calls_count = 5;

  struct timespec start, end;

  clock_gettime(CLOCK_REALTIME, &start);
  int result = -1;
  for (size_t i = 0; i < calls_count; ++i) {
    result = work(&v);
  }

  clock_gettime(CLOCK_REALTIME, &end);
  size_t time = (1000000000 * (end.tv_sec - start.tv_sec) +
          (end.tv_nsec - start.tv_nsec)) /
         1000;

  if (!output) {
    printf("Result : %d \n", result);
    printf("Time : %zu mks\n\n", time / calls_count);
  } else {
    FILE *file = fopen(output, "w");

    if (!file) {
      printf("Opening file failed\n");
      return 1;
    }

    fprintf(file, "Result : %d \n", result);
    fprintf(file, "Time : %zu mks\n\n", time / calls_count);

    if (fclose(file)) {
      printf("Closing file failed\n");
      return 1;
    }
  }

  if (!delete_vector(&v)) {
    printf("Deleting vector failed\n");
    return 1;
  }
  if (input) {
    free(input);
  }
  if (output) {
    free(output);
  }
  return 0;
}
