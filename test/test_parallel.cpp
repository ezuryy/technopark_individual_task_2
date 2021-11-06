#include <gtest/gtest.h>

extern "C" {
#include <parallel.h>
}

TEST(Test1, size_5_answer_40_last_temperature_jump_check) {
  FILE* file = fopen("../test/jump1.txt", "r");
  vector_t v;
  create_vector(&v);
  read_vector(&v, file);
  fclose(file);
  int result_parallel = find_max_temperature_jump(
      v.temperature_array, v.size, 0, v.size);  // parallel_process_job(&v);
  EXPECT_EQ(result_parallel, 40);
  delete_vector(&v);
}

TEST(Test2, size_6_answer_15_first_temperature_jump_check) {
  FILE* file = fopen("../test/jump2.txt", "r");
  vector_t v;
  create_vector(&v);
  read_vector(&v, file);
  fclose(file);
  int result_parallel = parallel_process_job(&v);
  EXPECT_EQ(result_parallel, 15);
  delete_vector(&v);
}

TEST(Test3, size_40_answer_87) {
  FILE* file = fopen("../test/jump3.txt", "r");
  vector_t v;
  create_vector(&v);
  read_vector(&v, file);
  fclose(file);
  int result_parallel = parallel_process_job(&v);
  EXPECT_EQ(result_parallel, 87);
  delete_vector(&v);
}

TEST(Test4, size_200_answer_183) {
  FILE* file = fopen("../test/jump4.txt", "r");
  vector_t v;
  create_vector(&v);
  read_vector(&v, file);
  fclose(file);
  int result_parallel = parallel_process_job(&v);
  EXPECT_EQ(result_parallel, 183);
  delete_vector(&v);
}

TEST(Test5, size_1000_answer_197) {
  FILE* file = fopen("../test/jump5.txt", "r");
  vector_t v;
  create_vector(&v);
  read_vector(&v, file);
  fclose(file);
  int result_parallel = parallel_process_job(&v);
  EXPECT_EQ(result_parallel, 197);
  delete_vector(&v);
}

TEST(Test6, size_25600_answer_199) {
  FILE* file = fopen("../test/jump6.txt", "r");
  vector_t v;
  create_vector(&v);
  read_vector(&v, file);
  fclose(file);
  int result_parallel = parallel_process_job(&v);
  EXPECT_EQ(result_parallel, 199);
  delete_vector(&v);
}

TEST(Test7, array_with_size_0) {
  FILE* file = fopen("../test/jump7.txt", "r");
  vector_t v;
  create_vector(&v);
  read_vector(&v, file);
  fclose(file);
  int result_parallel = parallel_process_job(&v);
  EXPECT_EQ(v.size, 0);
  EXPECT_EQ(result_parallel, -1);
  delete_vector(&v);
}

TEST(Test8, empty_array) {
  EXPECT_EQ(find_max(nullptr, 0), -1);
  EXPECT_EQ(parallel_process_job(nullptr), -1);
}
