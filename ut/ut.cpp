#include <gtest/gtest.h>
#include "task3.h"

#define LEN 10000
Row global[LEN];

TEST(HelloTest, BasicAssertions) {
  EXPECT_STRNE("hello", "world");
  prepare(global, LEN);
  prepare(global, LEN);
  task1(global, LEN);
  task2(global, LEN);
  task3(global, LEN);
  EXPECT_EQ(7 * 6, 42);
}



int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv); 
  return RUN_ALL_TESTS();
}
