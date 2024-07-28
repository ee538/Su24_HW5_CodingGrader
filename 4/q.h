#include <algorithm>
#include <climits>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

// We would like to put n students in a line. Each student is specified with an
// integer number in the input vector all_students.
// Some students are incompatible and cannot be next to each other. The list of
// incompatible students are given in `incompatible_students`.
//
// Write a function to find all possible ways that the students can be in a line
// such that no two incompatible students are next to each other.
//
// Example 1:
// all_students = {0, 1};
// incompatible_students= {};
// output = {{0, 1}, {1, 0}};

// Example 2:
// all_students =  {0, 1, 2};
// incompatible_students= {};
// output = {{0, 1, 2}, {0, 2, 1}, {1, 0, 2},
//           {1, 2, 0}, {2, 0, 1}, {2, 1, 0}};

// Example 3:
// all_students =  {0, 1, 2};
// incompatible_students= {{0, 1}};
// output = {{0, 2, 1}, {1, 2, 0}};

// Note that when `incompatible_students= {{0, 1}}`, it means that 0 cannot be
// placed before OR after 1.

std::vector<std::vector<int>> PutInLine(
    std::vector<int> &all_students,
    std::vector<std::set<int>> &incompatible_students);

// For your convenience a helper function's signature is given to you. Please
// use this and call it in `PutInLine` function.
void PutInLineHelper(std::vector<int> &all_students,
                     std::vector<std::set<int>> &incompatible_students,
                     std::vector<int> &cur_line,
                     std::vector<std::vector<int>> &results);
