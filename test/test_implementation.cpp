#include <gtest/gtest.h>

extern "C" {
#include <common_functions.h>
}

TEST(Test1, size_5_answer_40_last_temperature_jump_check) {
  FILE* file = fopen("../test/jump1.txt", "r");
  vector_t v;
  EXPECT_TRUE(create_vector(&v));
  EXPECT_TRUE(read_vector(&v, file));
  fclose(file);
  int result_consistent = work(&v);
  EXPECT_EQ(result_consistent, 40);
  EXPECT_TRUE(delete_vector(&v));
}

TEST(Test2, size_6_answer_15_first_temperature_jump_check) {
  FILE* file = fopen("../test/jump2.txt", "r");
  vector_t v;
  EXPECT_TRUE(create_vector(&v));
  EXPECT_TRUE(read_vector(&v, file));
  fclose(file);
  int result_consistent = work(&v);
  EXPECT_EQ(result_consistent, 15);
  EXPECT_TRUE(delete_vector(&v));
}

TEST(Test3, size_40_answer_87) {
  FILE* file = fopen("../test/jump3.txt", "r");
  vector_t v;
  EXPECT_TRUE(create_vector(&v));
  EXPECT_TRUE(read_vector(&v, file));
  fclose(file);
  int result_consistent = work(&v);
  EXPECT_EQ(result_consistent, 87);
  EXPECT_TRUE(delete_vector(&v));
}

TEST(Test4, size_200_answer_183) {
  FILE* file = fopen("../test/jump4.txt", "r");
  vector_t v;
  EXPECT_TRUE(create_vector(&v));
  EXPECT_TRUE(read_vector(&v, file));
  fclose(file);
  int result_consistent = work(&v);
  EXPECT_EQ(result_consistent, 183);
  EXPECT_TRUE(delete_vector(&v));
}

TEST(Test5, size_1000_answer_197) {
  FILE* file = fopen("../test/jump5.txt", "r");
  vector_t v;
  EXPECT_TRUE(create_vector(&v));
  EXPECT_TRUE(read_vector(&v, file));
  fclose(file);
  int result_consistent = work(&v);
  EXPECT_EQ(result_consistent, 197);
  EXPECT_TRUE(delete_vector(&v));
}

TEST(Test6, size_25600_answer_199) {
  FILE* file = fopen("../test/jump6.txt", "r");
  vector_t v;
  EXPECT_TRUE(create_vector(&v));
  EXPECT_TRUE(read_vector(&v, file));
  fclose(file);
  int result_consistent = work(&v);
  EXPECT_EQ(result_consistent, 199);
  EXPECT_TRUE(delete_vector(&v));
}

TEST(Test7, array_with_size_0) {
  FILE* file = fopen("../test/jump7.txt", "r");
  vector_t v;
  EXPECT_TRUE(create_vector(&v));
  EXPECT_TRUE(read_vector(&v, file));
  fclose(file);
  int result_consistent = work(&v);
  EXPECT_EQ(v.size, 0);
  EXPECT_EQ(result_consistent, -1);
  EXPECT_TRUE(delete_vector(&v));
}

TEST(Test8, empty_array) { EXPECT_EQ(work(nullptr), -1); }
