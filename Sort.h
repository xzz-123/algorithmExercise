#pragma once
#include <vector>
using namespace std;

class QuickSort {
//绿色注释为另一种实现方法——交换大法
	int partition(vector<int>&nums, int left, int right) {
		
		int pivot = nums[left];
		//int start = left;
		while (left < right) {
			while (left < right&&nums[right] >= pivot)--right;
			nums[left] = nums[right];
			while (left < right&&nums[left] <= pivot)++left;
			nums[right] = nums[left];
			//if (left < right)swap(nums[left], nums[right]);
		}
		//swap(nums[start], nums[left]);
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