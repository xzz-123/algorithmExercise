#pragma once
#include <algorithm>
#include <vector>
using namespace std;
//455. �ַ�����
//��������һλ�ܰ��ļҳ�����Ҫ����ĺ�����һЩС���ɡ����ǣ�ÿ���������ֻ�ܸ�һ����ɡ�
//
//��ÿ������ i������һ��θ��ֵ g[i]���������ú���������θ�ڵı��ɵ���С�ߴ磻����ÿ����� j������һ���ߴ� s[j] ��
//��� s[j] >= g[i]�����ǿ��Խ�������� j ��������� i ��������ӻ�õ����㡣���Ŀ���Ǿ���������Խ�������ĺ��ӣ��������������ֵ��
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