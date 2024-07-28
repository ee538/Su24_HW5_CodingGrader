#include <algorithm>
#include <climits>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

// In this problem we implement the knapsack problem in three ways.
//-----------------------------------------------------------------------------
// TODO: Implement the following functions in q.cc
//-----------------------------------------------------------------------------
// Implement the knapsack problem recursively.
int knapsack01(std::vector<int> &weights, std::vector<int> &values, int i,
               int capacity);
//-----------------------------------------------------------------------------
// Implement the knapsack problem recursively using memoization.
// Hint: in q.cc file, write a helper function called knapsack01_MemoHelper,
// which takes an extra parameter called memo. The memo variable should be
// instantiated in knapsack01_Memo and passed to the helper function.
int knapsack01_Memo(std::vector<int> &weights, std::vector<int> &values, int i,
                    int capacity);
//-----------------------------------------------------------------------------
// Implement the knapsack problem recursively using tabulation.
// This function should not be recursive.
int knapsack01_Table(std::vector<int> &weights, std::vector<int> &values, int i,
                     int capacity);
