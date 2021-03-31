#pragma once
#include <vector>
using namespace std;
class Subsets1 {
public:
	vector<vector<int>> subsets(vector<int>& nums) {
		vector<vector<int>>res;
		vector<int>cur;
		if (nums.size() == 0)return res;
		helper(res, cur, nums, 0);
		return res;
	}

	void helper(vector<vector<int>>&res, vector<int>cur, vector<int>nums, int index) {
		if (index == nums.size()) {
			res.push_back(cur);
			return;
		}
		cur.push_back(nums[index]);
		helper(res, cur, nums, index + 1);
		cur.pop_back();
		helper(res, cur, nums, index + 1);
	}
};

class Subsets2 {
public:

	vector<vector<int>> subsetsWithDup(vector<int>& nums) {
		vector<int>cur;
		vector<vector<int>>res;
		sort(nums.begin(), nums.end());
		helper(res, cur, nums, 0);
		return res;
	}

	void  helper(vector<vector<int>>&res, vector<int>&cur, vector<int>&nums, int index) {
		if (index == nums.size()) {
			res.push_back(cur);
			return;
		}
		cur.push_back(nums[index]);
		helper(res, cur, nums, index + 1);
		cur.pop_back();
		while (index + 1 < nums.size() && nums[index] == nums[index + 1]) {
			++index;
		}
		helper(res, cur, nums, index + 1);
	}

};
