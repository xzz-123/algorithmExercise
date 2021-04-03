#pragma once
#include <vector>
#include <algorithm>
#include <unordered_map>
using namespace std;
//给定一个double类型的浮点数base和int类型的整数exponent。求base的exponent次方。
//保证base和exponent不同时为0
class ComputePower {
public:
	double Power(double base, int exponent) {

		bool isNegative = false;
		if (exponent < 0) {
			exponent = -exponent;
			isNegative = true;
		}
		double res = Pow(base, exponent);
		return isNegative ? 1 / res : res;
	}

	double Pow(double base, int exponent) {
		if (exponent == 0)return 1;
		if (exponent == 1)return base;
		double res = Pow(base, exponent / 2);
		res *= res;
		return exponent % 2 == 0 ? res : res * base;
	}
};
//241. Different Ways to Add Parentheses
//Given a string expression of numbers and operators, return all possible results from computing all the 
//different possible ways to group numbers and operators.You may return the answer in any order.
//
//Input: expression = "2-1-1"
//	Output : [0, 2]
//	Explanation :
//	((2 - 1) - 1) = 0
//	(2 - (1 - 1)) = 2
class diffToC {
public:
	vector<int> diffWaysToCompute(string expression) {
		unordered_map<string, vector<int>>m;
		return  helper(expression, m);
	}
	vector<int> helper(string expression, unordered_map<string, vector<int>>&m) {
		int n = expression.size();
		vector<int>res;

		for (int i = 0;i < n;++i) {
			char c = expression[i];
			if ((c == '+') || (c == '-') || (c == '*')) {
				vector<int>res1, res2;
				string s1 = expression.substr(0, i);
				string s2 = expression.substr(i + 1);
				if (m.find(s1) != m.end())
					res1 = m[s1];
				else {
					res1 = helper(s1, m);

				}
				if (m.find(s2) != m.end())
					res2 = m[s2];
				else {
					res2 = helper(s2, m);

				}

				for (int num1 : res1) {
					for (int num2 : res2) {

						if (c == '+')res.push_back(num1 + num2);

						else if (c == '-')res.push_back(num1 - num2);

						else res.push_back(num1*num2);


					}
				}
			}
		}
		if (res.size() == 0)res.push_back(atoi(expression.c_str()));
		m[expression] = res;
		return res;
	}
};

class GenerateTrees {
public:
	vector<TreeNode*> helper(int start, int end) {
		vector<TreeNode*>ret;
		if (start > end) {
			ret.push_back(nullptr);
			return ret;
		}
		for (int i = start;i <= end;++i) {

			vector<TreeNode*>left = helper(start, i - 1);
			vector<TreeNode*>right = helper(i + 1, end);
			for (auto l : left)
				for (auto r : right) {
					TreeNode* root = new TreeNode(i);
					root->left = l;
					root->right = r;
					ret.push_back(root);
				}
		}
		return ret;
	}
	vector<TreeNode*> generateTrees(int n) {
		return helper(1, n);

	}
};
