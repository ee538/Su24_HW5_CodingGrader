#include <algorithm>
#include <climits>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

/*
Given an array of integers, find the maximum sum of a contiguous subarray
(subarray with at least one element).

For example:

makefile
Copy code
Input: [-2, 1, -3, 4, -1, 2, 1, -5, 4]
Output: 6 (Subarray [4, -1, 2, 1] has the largest sum 6)

Explanation:
In the given array, the subarray with the maximum sum is [4, -1, 2, 1], and its
sum is 6.


*/

// Recursive solution
int maxSubarraySumRecursive(const std::vector<int> &nums);

// Recursive solution with memoization
int maxSubarraySumMemoization(const std::vector<int> &nums);

// Tabulation (bottom-up) approach
int maxSubarraySumTabulation(const std::vector<int> &nums);
