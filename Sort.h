#pragma once
#include <vector>
using namespace std;
//75.Sort Colors
//Given an array nums with n objects colored red, white, or blue, sort them in - place so that objects of the same color are adjacent, with the colors in the order red, white, and blue.
//
//We will use the integers 0, 1, and 2 to represent the color red, white, and blue, respectively.
class SortColors {
public:
	void sortColors(vector<int>& nums) {
		int len = nums.size();
		int i = 0, left = 0, right = len - 1;
		while (i <= right) {
			if (nums[i] == 0) {
				swap(nums[i++], nums[left++]);
			}
			else if (nums[i] == 2) {
				swap(nums[i], nums[right--]);
			}
			else ++i;
		}
	}
};
class QuickSort {

	int partition(vector<int>&nums, int left, int right) {
		int pivot = nums[left];
		while (left < right) {
			while (left < right&&nums[right] >= pivot)--right;
			nums[left] = nums[right];
			while (left < right&&nums[left] <= pivot)++left;
			nums[right] = nums[left];
			
		}
		nums[left] = pivot;
		return left;
	}
	void quickSort(vector<int>&nums, int left, int right) {
		if (left < right) {
			int index = partition(nums, left, right);
			quickSort(nums, left, index - 1);
			quickSort(nums, index + 1, right);
		}
	}
public:
	vector<int> sortArray(vector<int>& nums) {
		quickSort(nums, 0, nums.size() - 1);
		return nums;
	}
};
//有一个整数数组，请你根据快速排序的思路，找出数组中第K大的数。

//给定一个整数数组a, 同时给定它的大小n和要找的K(K在1到n之间)，请返回第K大的数，保证答案存在。
class Findkth {
public:
	int findKth(vector<int> a, int n, int K) {
		// write code here
		K = n - K;//第K大的数在升序排列中的下标为n-K
		int left = 0, right = n - 1;
		while (left < right) {
			int j = partition(a, left, right);
			if (j < K)left = j + 1;
			else if (j > K)right = j - 1;
			else break;
		}
		return a[K];
	}

	int partition(vector<int>&a, int left, int right) {
		int pivot = a[left];

		int start = left;
		while (left < right) {
			while (left < right&&a[right] >= pivot)--right;
			while (left < right&&a[left] <= pivot)++left;
			if (left < right)swap(a[left], a[right]);
		}
		swap(a[start], a[left]);
		return left;
	}
};
class HeapSort {
public:
	void heapify(vector<int>&nums, int start, int end) {
		int dad = start;
		int son = dad * 2 + 1;
		while (son<=end)
		{
			if (son + 1 <= end && nums[son] < nums[son + 1])++son;
			if (nums[son] > nums[dad]) {
				swap(nums[son], nums[dad]);
				dad = son;
				son = dad * 2 + 1;
			}
			else
			{
				break;
			}
		}
	}
	void buildHeap(vector<int>& nums) {
		int len = nums.size();
		for (int i = len / 2 - 1;i >= 0;--i) {
			heapify(nums, i, len - 1);
		}
	}
	void heapSort(vector<int>&nums) {
		buildHeap(nums);
		int len = nums.size();
		for (int i = len - 1;i > 0;--i) {
			swap(nums[0], nums[i]);
			heapify(nums, 0, i - 1);
		}
	}
};

class MergeSort {
public:
	void merge(vector<int>&nums, int start, int mid, int end) {
		int p1 = start, p2 = mid + 1;
		int ind = 0;
		vector<int>tem(end - start + 1);
		while (p1 <= mid && p2 <= end)
		{
			if (nums[p1] <= nums[p2])
			{
				tem[ind++] = nums[p1++];
			}
			else
			{
				tem[ind++] = nums[p2++];
			}
		}
		while (p1 <= mid)
		{
			tem[ind++] = nums[p1++];
		}
		while (p2 <= end)
		{
			tem[ind++] = nums[p2++];
		}
		copy(tem.begin(), tem.end(), nums.begin() + start);
	}
	void mergerSort(vector<int>&nums, int start, int end) {
		if (start < end)
		{
			int mid = start + ((end - start) >> 1);
			mergerSort(nums, start, mid);
			mergerSort(nums, mid + 1, end);
			merge(nums, start, mid, end);
		}

	}
};

class BubbleSort {
	void bubbleSort(vector<int>&nums) {
		int len = nums.size();
		for (int i = 0;i < len;++i) {
			for (int j = 0;j < len - i - 1;++j) {
				if (nums[j] > nums[j + 1])swap(nums[j], nums[j + 1]);
			}
		}
	}
public:
	vector<int> sortArray(vector<int>& nums) {
		bubbleSort(nums);return nums;
	}
};

class InsertSort {
	void insertSort(vector<int>&nums) {
		int len = nums.size();
		for (int i = 1;i < len;++i) {
			int cur = nums[i];
			int j = i - 1;
			while (j >= 0 && cur < nums[j])
			{
				nums[j + 1] = nums[j];
				--j;
			}
			nums[j + 1] = cur;

		}


	}
public:
	vector<int> sortArray(vector<int>& nums) {
		insertSort(nums);return nums;
	}

};

class SelectSort {
	void selectSort(vector<int>&nums) {
		int len = nums.size();

		for (int i = 0;i < len-1;++i) {
			int minInd = i;
			for (int j = i + 1;j < len;++j) {
				if (nums[minInd] > nums[j])minInd = j;
			}
			swap(nums[minInd], nums[i]);
		}
	}
public:
	vector<int> sortArray(vector<int>& nums) {
		selectSort(nums);return nums;
	}

};