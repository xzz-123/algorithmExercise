#pragma once
#include <vector>
#include <algorithm>
using namespace std;
//把一个数组最开始的若干个元素搬到数组的末尾，我们称之为数组的旋转。输入一个递增排序的数组的一个旋转，
//输出旋转数组的最小元素。例如，数组 [3, 4, 5, 1, 2] 为[1, 2, 3, 4, 5] 的一个旋转，该数组的最小值为1。
class minInRotateArray {
public:
	int minArray(vector<int>& numbers) {
		int n = numbers.size();
		if (n == 0)return 0;
		int l = 0, r = n - 1;
		while (l < r) {
			int mid = l + (r - l) / 2;
			if (numbers[mid] < numbers[r])
				r = mid;
			else if (numbers[mid] > numbers[r])
				l = mid + 1;
			else --r;
		}
		return numbers[l];
	}
};
//一个整型数组 nums 里除两个数字之外，其他数字都出现了两次。请写程序找出这两个只出现一次的数字。要求时间复杂度是O(n)，空间复杂度是O(1)。
class findTwoNumbersAppearOnce {
public:
	vector<int> singleNumbers(vector<int>& nums) {
		int n = 0;
		for (int &i : nums) {
			n ^= i;
		}
		int digE1 = 1;
		while ((digE1&n) == 0) {
			digE1 <<= 1;
		}
		int a = 0, b = 0;
		for (int &i : nums) {
			if (digE1&i)
				a ^= i;
			else
				b ^= i;
		}
		return vector<int>{a, b};
	}
};
//410. Split Array Largest Sum
//
//Given an array nums which consists of non - negative integers and an integer m, you can split the array into 
//m non - empty continuous subarrays.
//
//Write an algorithm to minimize the largest sum among these m subarrays.


class SplitArray {
private:
	int split(int mid, vector<int>&nums) {
		int pieces = 1, curSum = 0;
		for (int i = 0;i < nums.size();++i) {
			if (curSum + nums[i] > mid) {
				++pieces;
				curSum = nums[i];
			}
			else {
				curSum += nums[i];
			}
		}
		return pieces;
	}
public:
	int splitArray(vector<int>& nums, int m) {
		int maxEle = INT_MIN, sum = 0;
		for (int &num : nums) {
			maxEle = max(maxEle, num);
			sum += num;
		}
		int low = maxEle, high = sum;
		while (low < high) {
			int mid = low + (high - low) / 2;
			int pieces = split(mid, nums);
			if (pieces > m) {
				low = mid + 1;
			}
			else
				high = mid;

		}
		return low;
	}

};
//74. Search a 2D Matrix
//
//Write an efficient algorithm that searches for a value in an m x n matrix.This matrix has the following properties :
//
//Integers in each row are sorted from left to right.
//The first integer of each row is greater than the last integer of the previous row.
class SearchMatrix {
public:
	bool searchMatrix(vector<vector<int>>& matrix, int target) {
		int rows = matrix.size(), cols = matrix[0].size();
		int len = rows * cols;
		int left = 0, right = len - 1;
		while (left <= right) {
			int mid = left + ((right - left) >> 1);
			int x = mid / cols, y = mid % cols;
			int cur = matrix[x][y];
			if (cur == target)return true;
			else if (cur > target)right = mid - 1;
			else left = mid + 1;
		}
		return false;
	}
};

//33. Search in Rotated Sorted Array
//There is an integer array nums sorted in ascending order(with distinct values).
//
//Prior to being passed to your function, nums is rotated at an unknown pivot index k(0 <= k < nums.length) such that the resulting array 
//is[nums[k], nums[k + 1], ..., nums[n - 1], nums[0], nums[1], ..., nums[k - 1]](0 - indexed).For example, [0, 1, 2, 4, 5, 6, 7] might be rotated 
//at pivot index 3 and become[4, 5, 6, 7, 0, 1, 2].
//
//Given the array nums after the rotation and an integer target, return the index of target if it is in nums, or -1 if it is not in nums.
class Search {
public:
	int search(vector<int>& nums, int target) {
		int len = nums.size();
		int left = 0, right = len - 1;
		while (left <= right) {
			int mid = left + ((right - left) >> 1);
			if (nums[mid] == target)return mid;
			//如果mid在数组1中
			if (nums[mid] >= nums[left]) {
				//如果target也在数组1中
				if (target >= nums[left]) {
					if (nums[mid] > target)right = mid - 1;
					else left = mid + 1;
				}
				else {
					left = mid + 1;
				}
			}
			else {
				if (target < nums[left]) {
					if (nums[mid] > target)right = mid - 1;
					else left = mid + 1;
				}
				else {
					right = mid - 1;
				}
			}
		}
		return -1;
	}
};
//81. Search in Rotated Sorted Array II.with duplicates
class Search2 {
public:
	bool search(vector<int>& nums, int target) {
		int len = nums.size();
		int left = 0, right = len - 1;
		while (left <= right) {
			int mid = left + ((right - left) >> 1);
			if (nums[mid] == target)return true;
			if (nums[mid] == nums[left] && nums[left] == nums[right]) { ++left;--right; }
			else if (nums[mid] >= nums[left]) {
				if (target >= nums[left] && target < nums[mid])right = mid - 1;
				else left = mid + 1;
			}
			else {
				if (target<nums[left] && target>nums[mid])left = mid + 1;
				else right = mid - 1;
			}
		}
		return  false;
	}
};