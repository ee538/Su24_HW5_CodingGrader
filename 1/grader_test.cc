#include <iostream>
#include <string>

#include "gtest/gtest.h"
#include "q.h"

//-----------------------------------------------------------------------------
// Write some test cases for each function.
//-----------------------------------------------------------------------------
TEST(Fibonacci, Test1) {
  EXPECT_EQ(Fibonacci(-1), 1);
  EXPECT_EQ(Fibonacci(0), 1);
  EXPECT_EQ(Fibonacci(1), 1);
}

TEST(Fibonacci, Test2) {
  std::vector<int> expecteds{1, 1, 2, 3, 5, 8, 13, 21, 34};
  for (int i = 0; i < expecteds.size(); ++i) {
    EXPECT_EQ(Fibonacci(i), expecteds[i]);
  }
}
