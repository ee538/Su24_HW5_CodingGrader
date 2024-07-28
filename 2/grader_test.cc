#include <iostream>
#include <map>
#include <vector>

#include "q.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"
using ::testing::UnorderedElementsAreArray;

template <class T> std::string CollectionToString(T input) {
  std::string result = "{ ";
  unsigned int count = 0;
  for (auto n : input) {
    count++;
    result += std::to_string(n);
    if (count < input.size()) {
      result += ", ";
    }
  }
  result += " }";
  return result;
}

//-----------------------------------------------------------------------------
// Write some test cases for each function.
// This is a parameterized test to test several inputs with multiple functions.
// We write a parameterized tests where the input is one parameter, and the
// function to run on that input is another parameter. To see how parameterized
// tests work, see here: https://www.youtube.com/watch?v=JJqRlSTQlh4&t=2159s
//-----------------------------------------------------------------------------
// Stores the input, which consists of a vector of integers and the expected
// maximum subarray sum.
struct MyInputType {
  std::vector<int> nums;
  int expected;

  // Used by google test to print objects of this class in the test output.
  friend void PrintTo(const MyInputType &myInput, std::ostream *os) {
    *os << myInput.DebugString();
  }

  // Returns a string representation of the instance for debugging.
  std::string DebugString() const {
    return "\nnums: " + CollectionToString(nums) +
           ", expected: " + std::to_string(expected) + "\n";
  }
};

std::vector<std::pair<std::string, MyInputType>> input_map = {
    {"EmptyArray", MyInputType{{}, 0}},
    {"AllNegatives", MyInputType{{-2, -3, -1, -5}, -1}},
    {"MixedValues", MyInputType{{-2, 1, -3, 4, -1, 2, 1, -5, 4}, 6}},
    {"SinglePositive", MyInputType{{5}, 5}},
    {"AllPositives", MyInputType{{1, 2, 3, 4}, 10}},
};

// The function that is passed to the tests
using MyFunctionType = std::function<int(const std::vector<int> &)>;

std::vector<std::pair<std::string, MyFunctionType>> function_map = {
    {"Recursive", maxSubarraySumRecursive},
    {"Memoization", maxSubarraySumMemoization},
    {"Tabulation", maxSubarraySumTabulation},
};

void PrintTo(const std::tuple<std::pair<std::string, MyFunctionType>,
                              std::pair<std::string, MyInputType>> &input,
             std::ostream *os) {
  *os << "Function: " << std::get<0>(input).first << "\n"
      << "Input: " << std::get<1>(input).first << ": "
      << std::get<1>(input).second.DebugString();
}

class MaxSubarraySumTest
    : public testing::TestWithParam<
          std::tuple<std::pair<std::string, MyFunctionType>,
                     std::pair<std::string, MyInputType>>> {};

INSTANTIATE_TEST_SUITE_P(
    MaxSubarraySumCases, MaxSubarraySumTest,
    testing::Combine(testing::ValuesIn(function_map),
                     testing::ValuesIn(input_map)),
    [](const testing::TestParamInfo<MaxSubarraySumTest::ParamType> &info) {
      return std::get<0>(info.param).first + "_" +
             std::get<1>(info.param).first;
    });

TEST_P(MaxSubarraySumTest, Test) {
  auto parameter = GetParam();

  // Get the function.
  auto maxSubarraySum_function = std::get<0>(parameter).second;

  // Get the input.
  auto [nums, expected] = std::get<1>(parameter).second;

  EXPECT_EQ(maxSubarraySum_function(nums), expected);
}
