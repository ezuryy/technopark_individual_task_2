#include <gtest/gtest.h>

extern "C" {
#include <common_functions.h>
}

TEST(Test1, create_vector) {
  vector_t v;
  EXPECT_TRUE(create_vector(&v));
  EXPECT_EQ(v.size, 0);
  EXPECT_EQ(v.capacity, 1);
  EXPECT_TRUE(delete_vector(&v));
}

TEST(Test2, push_back) {
  vector_t v;
  EXPECT_TRUE(create_vector(&v));
  push_back(&v, 1);
  EXPECT_EQ(v.size, 1);
  EXPECT_EQ(v.capacity, 1);
  push_back(&v, 2);
  EXPECT_EQ(v.size, 2);
  EXPECT_EQ(v.capacity, 2);
  push_back(&v, 3);
  EXPECT_EQ(v.size, 3);
  EXPECT_EQ(v.capacity, 4);
  EXPECT_TRUE(delete_vector(&v));
}

TEST(Test4, test_max_jump_end) {
  vector_t v;
  create_vector(&v);

  FILE* file;
  file = fopen("../test/jump1.txt", "r");
  EXPECT_TRUE(read_vector(&v, file));
  fclose(file);

  int result =
      find_max_temperature_jump(v.temperature_array, v.size, 0, v.size);
  EXPECT_EQ(result, 40);
  EXPECT_TRUE(delete_vector(&v));
}

TEST(Test5, test_max_jump_start) {
  vector_t v;
  create_vector(&v);

  FILE* file;
  file = fopen("../test/jump2.txt", "r");
  EXPECT_TRUE(read_vector(&v, file));
  fclose(file);

  int result1 =
      find_max_temperature_jump(v.temperature_array, v.size, 0, v.size);
  EXPECT_EQ(result1, 15);

  int result2 =
      find_max_temperature_jump(v.temperature_array, v.size, 1, v.size);
  EXPECT_EQ(result2, 15);

  int result3 = find_max_temperature_jump(nullptr, 0, 0, 0);
  EXPECT_EQ(result3, -1);

  EXPECT_TRUE(delete_vector(&v));
}

TEST(Test6, null) {
  EXPECT_FALSE(create_vector(nullptr));
  EXPECT_FALSE(push_back(nullptr, 1));

  vector_t v;
  EXPECT_TRUE(create_vector(&v));

  EXPECT_FALSE(read_vector(nullptr, stdin));
  EXPECT_FALSE(read_vector(&v, nullptr));

  EXPECT_TRUE(delete_vector(&v));
  EXPECT_FALSE(delete_vector(nullptr));
}
