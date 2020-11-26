#include "hashQuestion.h"

vector<int> twoSum(vector<int>& nums, int target)
{
	unordered_map<int, int>m;
	vector<int>res;
	for (int i = 0; i < nums.size(); ++i){
		auto iter = m.find(nums[i]);
		if (iter != m.end())
		{
			res.push_back(iter->second);
			res.push_back(i);
			break;
		}
		m[target - nums[i]] = i;
	}
	return res;
}

bool containsDuplicate(vector<int>& nums)
{
	unordered_set<int>s;
	bool duplicate = false;
	for (int i : nums){
		if (s.find(i) != s.end())
		{
			duplicate = true;
			break;
		}
		s.insert(i);
	}
	return duplicate;
}

int findLHS(vector<int>& nums)
{
	unordered_map<int, int>m;
	for (int num : nums){
		m[num]++;
	}
	int ret = 0;

	for (auto iter = m.begin(); iter != m.end(); ++iter){
		if (m.count(iter->first - 1) > 0)
			ret = max(ret, m[iter->first - 1] + iter->second);
	}
	return ret;
}

int longestConsecutive(vector<int>& nums)
{
	unordered_set<int>s(nums.begin(), nums.end());
	int ret = 0, cur = 1;
	for (int num : nums){
		if (s.find(num) == s.end())continue;
		s.erase(num);
		int pre = num - 1, next = num + 1;
		while (s.find(pre) != s.end())s.erase(pre--);
		while (s.find(next) != s.end())s.erase(next++);
		ret = max(ret, next - pre - 1);
	}
	return ret;
}
