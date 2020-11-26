#pragma once

#include <vector>
#include <unordered_map>
#include <unordered_set>
using namespace std;
//Given an array of integers nums and an integer target, return indices of the two numbers such that they add up to target.
//
//You may assume that each input would have exactly one solution, and you may not use the same element twice.
//
//You can return the answer in any order.
vector<int> twoSum(vector<int>& nums, int target);
//Given an array of integers, find if the array contains any duplicates.
//
//Your function should return true if any value appears at least twice in the array, and it should return false if every element is distinct.
bool containsDuplicate(vector<int>& nums);
//We define a harmonious array as an array where the difference between its maximum value and its minimum value is exactly 1.

//Given an integer array nums, return the length of its longest harmonious subsequence among all its possible subsequences.

int findLHS(vector<int>& nums);
//Given an unsorted array of integers nums, return the length of the longest consecutive elements sequence.

//Follow up : Could you implement the O(n) solution ?
int longestConsecutive(vector<int>& nums);