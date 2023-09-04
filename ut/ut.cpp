#include <gtest/gtest.h>
#include "task3.h"
#include <random>
#define LEN 100000
Row global[LEN];

TEST(HelloTest, BasicAssertions) {
  EXPECT_STRNE("hello", "world");
  prepare(global, LEN);
  task0(global, LEN);
  EXPECT_EQ(task1(global, LEN), task2(global, LEN));
  EXPECT_EQ(task1(global, LEN), task3(global, LEN));
  EXPECT_EQ(task2(global, LEN), task3(global, LEN));
  
  EXPECT_EQ(task3_stl_sort(global, LEN), task3(global, LEN));
  EXPECT_EQ(task2b(global, LEN), task3(global, LEN));
  EXPECT_EQ(task2b(global, LEN), task3b(global, LEN));
  EXPECT_EQ(task3b_stl_sort(global, LEN), task3(global, LEN));
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv); 
  return RUN_ALL_TESTS();
}
