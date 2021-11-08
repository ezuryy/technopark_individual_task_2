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
  create_vector(&v);
  if (!input) {
    read_vector(&v, stdin);
  } else {
    FILE *file = fopen(input, "r");

    if (!file) {
      return 1;
    }

    read_vector(&v, file);

    if (fclose(file)) {
      return 1;
    }
  }

  struct timespec start, end;
  long int time;

  clock_gettime(CLOCK_REALTIME, &start);

  int result = work(&v);

  clock_gettime(CLOCK_REALTIME, &end);
  time =
      1000000000 * (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec);

  if (!output) {
    printf("Result == %d \n", result);
    printf("Time : %ld mks\n\n", time / 1000);
  } else {
    FILE *file = fopen(output, "w");

    if (!file) {
      return 1;
    }

    fprintf(file, "Result == %d \n", result);
    fprintf(file, "Time : %ld mks\n\n", time / 1000);

    if (fclose(file)) {
      return 1;
    }
  }

  delete_vector(&v);
  if (input) {
    free(input);
  }
  if (output) {
    free(output);
  }
  return 0;
}
