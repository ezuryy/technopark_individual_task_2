#include <consistent.h>
#include <parallel.h>

int main() {
  vector_t v;
  create_vector(&v);
  read_vector(&v, stdin);
  print_vector(&v);

  // consistent implementation
  clock_t consistent_time_start = clock();
  int result_consistent = consistent_job(&v);
  clock_t consistent_time_end = clock();
  printf("Result consistent == %d \n", result_consistent);
  printf("Consistent time : %ld mks\n\n",
         (long int)(consistent_time_end - consistent_time_start));

  // parallel implementation

  struct timespec mt1, mt2;
  long int tt;

  clock_gettime(CLOCK_REALTIME, &mt1);

  int result_parallel = parallel_process_job(&v);

  clock_gettime(CLOCK_REALTIME, &mt2);
  tt = 1000000000 * (mt2.tv_sec - mt1.tv_sec) + (mt2.tv_nsec - mt1.tv_nsec);

  printf("Result parallel == %d \n", result_parallel);
  printf("Parallel time : %ld mks\n\n", tt / 1000);
  delete_vector(&v);
  return 0;
}
