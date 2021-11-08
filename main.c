#include <getopt.h>
#include <time.h>

#include "common_functions.h"

int main(int argc, char *argv[]) {
  int opt;
  char *opts = "-:i:o:";
  char *input = NULL;
  char *output = NULL;

  while ((opt = getopt(argc, argv, opts)) != -1) {
    switch (opt) {
      case 'i':
        input = optarg;
        break;
      case 'o':
        output = optarg;
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
  if (input == NULL) {
    read_vector(&v, stdin);
  } else {
    FILE *file = fopen(input, "rb");

    if (!file) {
      return 1;
    }

    read_vector(&v, file);

    if (fclose(file)) {
      return 1;
    }
  }

  struct timespec mt1, mt2;
  long int tt;

  clock_gettime(CLOCK_REALTIME, &mt1);

  int result = work(&v);

  clock_gettime(CLOCK_REALTIME, &mt2);
  tt = 1000000000 * (mt2.tv_sec - mt1.tv_sec) + (mt2.tv_nsec - mt1.tv_nsec);

  if (output == NULL) {
    printf("Result == %d \n", result);
    printf("Time : %ld mks\n\n", tt / 1000);
  } else {
    FILE *file = fopen(output, "wb");

    if (!file) {
      return 1;
    }

    fprintf(file, "Result == %d \n", result);
    fprintf(file, "Time : %ld mks\n\n", tt / 1000);

    if (fclose(file)) {
      return 1;
    }
  }

  delete_vector(&v);
  return 0;
}
