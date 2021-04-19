#pragma once
#include <algorithm>
#include <vector>
using namespace std;
//455. 分发饼干
//假设你是一位很棒的家长，想要给你的孩子们一些小饼干。但是，每个孩子最多只能给一块饼干。
//
//对每个孩子 i，都有一个胃口值 g[i]，这是能让孩子们满足胃口的饼干的最小尺寸；并且每块饼干 j，都有一个尺寸 s[j] 。
//如果 s[j] >= g[i]，我们可以将这个饼干 j 分配给孩子 i ，这个孩子会得到满足。你的目标是尽可能满足越多数量的孩子，并输出这个最大数值。
class FindContentChildren {
public:
	int findContentChildren(vector<int>& g, vector<int>& s) {
		sort(g.begin(), g.end());
		sort(s.begin(), s.end());

		int res = 0;
		for (int i = 0, j = 0;i < g.size() && j < s.size();) {
			if (g[i] <= s[j]) {
				res++;
				++i;++j;
			}
			else ++j;
		}
		return res;
	}
};


class ReconstructQueue {
public:
	vector<vector<int>>res;
	vector<vector<int>> reconstructQueue(vector<vector<int>>& people) {
		sort(people.begin(), people.end(), [](vector<int>&a, vector<int>&b) {return a[0] == b[0] ? a[1]<b[1] : a[0]>b[0];});
		for (int i = 0;i < people.size();++i) {
			res.insert(res.begin() + people[i][1], people[i]);
		}
		return res;
	}

};