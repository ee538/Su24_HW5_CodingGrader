#include <iostream>
#include <map>
#include <vector>

#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "q.h"
using ::testing::UnorderedElementsAreArray;

template <class T>
std::string CollectionToString(T input) {
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

// Stores the input, which consists of values, weights, capacity and the
// expected value.
struct MyInputType {
  std::vector<int> values;
  std::vector<int> weights;
  int capacity;
  int expected;

  // This function will be called by testing::PrintToString.
  friend void PrintTo(const MyInputType &myInput, std::ostream *os) {
    *os << myInput.DebugString();
  }

  // This function will be used by google test to print objects of this class in
  // the test output.
  std::string DebugString() const {
    std::string result;
    return result + "\nvalues: " + CollectionToString(values) +
           ", weights: " + CollectionToString(weights) +
           ", capacity: " + std::to_string(capacity) +
           ", expected: " + std::to_string(expected) + "\n";
  }
};

// The input to the test. Each test case has a different value of MyInputType
std::vector<std::pair<std::string, MyInputType>> input_map = {
    {"ZeroItems",  // Test name
     MyInputType{
         {},   // values
         {},   // weights
         100,  // capacity
         0,    // expected
     }},
    {"ZeroCapacity",  // Test name
     MyInputType{
         {1, 2, 2, 4, 10},  // values
         {1, 2, 1, 12, 4},  // weights
         0,                 // capacity
         0,                 // expected
     }},
    {"OneItem",  // Test name
     MyInputType{
         {100},  // values
         {12},   // weights
         15,     // capacity
         100,    // expected
     }},
    {"TwoItemImpossible",  // Test name
     MyInputType{
         {100, 1000},  // values
         {12, 12},     // weights
         1,            // capacity
         0,            // expected
     }},
    {"ThreeItems",  // Test name
     MyInputType{
         {60, 100, 120},  // values
         {10, 20, 30},    // weights
         50,              // capacity
         220,             // expected
     }},
    {"FourItems",  // Test name
     MyInputType{
         {1, 2, 2, 4, 10},  // values
         {1, 2, 1, 12, 4},  // weights
         15,                // capacity
         15,                // expected
     }},

};

// The function that is passed to the tests
using MyFunctionType =
    std::function<int(std::vector<int> &, std::vector<int> &, int, int)>;

std::vector<std::pair<std::string, MyFunctionType>> function_map = {
    //
    {"knapsack01", knapsack01},
    {"knapsack01_Memo", knapsack01_Memo},
    {"knapsack01_Table", knapsack01_Table}
    //
};

// This function is called by google test to print the parameter of each test
// which consists of the function and the input.
void PrintTo(const std::tuple<std::pair<std::string, MyFunctionType>,
                              std::pair<std::string, MyInputType>> &input,
             std::ostream *os) {
  *os << "Function: " << std::get<0>(input).first << "\n"
      << "Input: " << std::get<1>(input).first << ": "
      << std::get<1>(input).second.DebugString();
}

// Creating the test suite.
class KnapsackTest : public testing::TestWithParam<
                         std::tuple<std::pair<std::string, MyFunctionType>,
                                    std::pair<std::string, MyInputType>>> {};

// Instantiating the test.
INSTANTIATE_TEST_SUITE_P(
    GraderTest, KnapsackTest,
    // Cartesian product of various functions and inputs will be fed to the
    // test.
    testing::Combine(testing::ValuesIn(function_map),
                     testing::ValuesIn(input_map)),
    // A function that is used to print each generated test.
    [](const testing::TestParamInfo<KnapsackTest::ParamType> &info) {
      return std::get<0>(info.param).first + "_" +
             std::get<1>(info.param).first;
    });

// The single parameterized test.
TEST_P(KnapsackTest, Test) {
  auto parameter = GetParam();

  // Get the function.
  auto knapsack_function = std::get<0>(parameter).second;

  // Get the input.
  auto [values, weights, capacity, expected] = std::get<1>(parameter).second;

  EXPECT_THAT(knapsack_function(weights, values, values.size() - 1, capacity),
              expected);
}
