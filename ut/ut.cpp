#include <gtest/gtest.h>
#include "task3.h"
#include <random>
#define LEN 100000
Row global[LEN];

TEST(HelloTest, BasicAssertions) {
  prepare(global, LEN);
  warm(global, LEN);
  EXPECT_EQ(task1(global, LEN), task2(global, LEN));
  EXPECT_EQ(task1(global, LEN), task3_stl_sort(global, LEN));
  EXPECT_EQ(task2(global, LEN), task3_stl_sort(global, LEN));
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv); 
  return RUN_ALL_TESTS();
}
