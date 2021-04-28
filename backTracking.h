#pragma once
#include <vector>
#include <algorithm>
#include <numeric>
#include <set>
using namespace std;
//与下面是同一个问题，回溯法的不同写法
class Subsets {
public:
	vector<vector<int>>res;
	vector<int>cur;
	vector<vector<int>> subsets(vector<int>& nums) {
		int n = nums.size();
		helper(0, nums);
		return res;
	}

	void helper(int ind, vector<int>&nums) {
		for (int i = ind;i < nums.size();++i) {
			cur.push_back(nums[i]);
			res.push_back(cur);
			helper(i + 1, nums);
			cur.pop_back();
		}
	}
};
//nums中元素不重复，找到所有不重复的子集
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
class SubsetsWithDup {
public:
	vector<int>cur;
	vector<vector<int>>res;
	vector<vector<int>> subsetsWithDup(vector<int>& nums) {
		sort(nums.begin(), nums.end());
		backTrak(nums, 0);
		return res;
	}
	void backTrak(vector<int>&nums, int start) {
		for (int i = start;i < nums.size();++i) {
			if (i > start&&nums[i] == nums[i - 1])continue;
			cur.push_back(nums[i]);
			res.push_back(cur);
			backTrak(nums, i + 1);
			cur.pop_back();
		}
	}
};

//nums元素有重复，找到所有不重复的子集
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
//N皇后问题，在n×n的棋盘里放置n个皇后，使得皇后互相之间不能攻击，（皇后可以攻击同行同列以及同对角线反对角线的敌人）找出所有可能的放置情况
class N_Queen {
public:
	vector<vector<string>> solveNQueens(int n) {
		vector<vector<string>> res;
		vector<string>cur(n, string(n, '.'));
		helper(res, cur, 0, n);
		return res;
	}

	void helper(vector<vector<string>>&res, vector<string>&cur, int rowIndex, int n) {
		if (rowIndex == n) {
			res.push_back(cur);
			return;
		}
		for (int colIndex = 0;colIndex < n;++colIndex) {
			if (isValid(rowIndex, colIndex, cur)) {
				cur[rowIndex][colIndex] = 'Q';
				helper(res, cur, rowIndex + 1, n);
				cur[rowIndex][colIndex] = '.';
			}
		}
	}

	bool isValid(int rowIndex, int colIndex, vector<string>&cur) {
		for (int i = 0;i != rowIndex;++i) {
			if (cur[i][colIndex] == 'Q')
				return false;
		}

		for (int i = rowIndex - 1, j = colIndex - 1;i >= 0&&j >= 0;--i, --j) {
			if (cur[i][j] == 'Q')return false;
		}

		for (int i = rowIndex - 1, j = colIndex + 1;i >= 0&&j < cur.size();--i, ++j) {
			if (cur[i][j] == 'Q')return false;
		}
		return true;
	}
};
extern const int aaa;
class SudokuSolver {
public:
	void solveSudoku(vector<vector<char>>& board) {
		
		helper(board, 0, 0);
	}
	
	bool helper(vector<vector<char>>&board, int rowIndex, int colIndex) {
		if (rowIndex == 9) {
			return true;
		}
		if (board[rowIndex][colIndex] != '.') {
			if (colIndex == 8)
				return helper(board, rowIndex + 1, 0);
			else return helper(board, rowIndex, colIndex + 1);
		}
		for (int i = 1;i < 10;++i) {
			if (isValid(rowIndex, colIndex, i, board)) {
				board[rowIndex][colIndex] = '0' + i;
				if (colIndex == 8) {
					if (helper(board, rowIndex + 1, 0))return true;
				}
				else if (helper(board, rowIndex, colIndex + 1)) return true;
				board[rowIndex][colIndex] = '.';
			}
		}
		return false;
	}
	bool isValid(int rowIndex, int colIndex, int n, vector<vector<char>>&cur) {
		for (int i = 0;i < 9;++i) {
			if (cur[rowIndex][i] == n+'0')return false;
			if (cur[i][colIndex] == n + '0')return false;
		}
		int rb = rowIndex / 3, cb = colIndex / 3;
		for (int i = rb * 3;i < rb * 3 + 3;++i) {
			for (int j = cb * 3;j < cb * 3 + 3;++j) {
				if (cur[i][j] == n+'0')return false;
			}
		}
		return true;
	}
};

class Shopping_offer {
private:
	int min;

	bool spIsValid(vector<int>&needs, vector<int>&offer) {
		int n = needs.size();
		for (int i = 0;i < n;++i) {
			if (needs[i] < offer[i])return false;
		}
		return true;
	}
	void helper(vector<int>&price, vector<vector<int>>&special, vector<int>&needs, int used, int index) {
		if (used >= min)return;
		if (index == special.size()) {
			used += inner_product(price.begin(), price.end(), needs.begin(), 0);
			min = std::min(used, min);
			return;
		}
		vector<int>offer = special[index];
		int n = price.size();
		if (spIsValid(needs, offer)) {

			vector<int>updateNeeds(needs);
			for (int i = 0;i < n;++i) {
				updateNeeds[i] -= offer[i];
			}
			helper(price, special, updateNeeds, used + offer[n], index);
		}

		helper(price, special, needs, used, index + 1);
	}
public:

	int shoppingOffers(vector<int>& price, vector<vector<int>>& special, vector<int>& needs) {

		min = inner_product(price.begin(), price.end(), needs.begin(), 0);
		helper(price, special, needs, 0, 0);
		return min;
	}

};
//判断在一个矩阵中是否存在一条包含某字符串所有字符的路径。路径可以从矩阵中的任意一个格子开始，
//每一步可以在矩阵中向上下左右移动一个格子。如果一条路径经过了矩阵中的某一个格子，则该路径不能再进入该格子。
class Exist {
public:
	int rowD[4] = { 0,0,1,-1 };
	int colD[4] = { 1,-1,0,0 };
	vector<vector<bool>> visitied;
	bool exist(vector<vector<char>>& board, string word) {
		visitied.assign(board.size(), vector<bool>(board[0].size()));
		for (int i = 0;i < board.size();++i) {
			for (int j = 0;j < board[0].size();++j) {
				if (backTrack(board, word, i, j, 0))return true;
			}
		}
		return false;
	}

	bool backTrack(vector<vector<char>>& board, string word, int x, int y, int id) {
		if (board[x][y] != word[id])return false;
		if (id == word.size() - 1) {
			return true;
		}
		visitied[x][y] = true;
		for (int i = 0;i < 4;++i) {
			int rr = x + rowD[i], cc = y + colD[i];
			if (rr >= board.size() || rr < 0 || cc < 0 || cc >= board[0].size() || visitied[rr][cc])continue;
			if (backTrack(board, word, rr, cc, id + 1))return true;
		}
		visitied[x][y] = false;
		return false;
	}
};
//317.Shortest Distance from All Buildings
//You want to build a house on an empty land which reaches all buildings in the shortest amount of distance.
//You can only move up, down, left and right.You are given a 2D grid of values 0, 1 or 2, where:
//Each 0 marks an empty land which you can pass by freely..Each 1 marks a building which you cannot pass through.
//Each 2 marks an obstacle which you cannot pass through.
//                       1-0-2-0-1
//                       | | | | |
//                       0-0-0-0-0
//                       | | | | |
//                       0-0-1-0-0
class ShortestD{
private:
	int rowDir[4] = { 0,0,1,-1 };
	int colDir[4] = { 1,-1,0,0 };
	bool isValid(vector<vector<int>>&grid, int rr, int cc, vector<vector<bool>>&visitied) {
		int rows = grid.size(), cols = grid[0].size();
		if (rr >= rows || cc >= cols || rr < 0 || cc < 0)return false;
		if (visitied[rr][cc])return false;
		if (grid[rr][cc] == 0)return true;
		return false;
	}
	void bfs(vector<vector<int>>&grid, vector<vector<int>>&distance, vector<vector<int>>&canReach, int rowIndex,
		int colIndex) {
		int rows = grid.size(), cols = grid[0].size();
		vector<vector<bool>>visitied(rows, vector<bool>(cols, false));
		int d = 0;
		queue<pair<int, int>>q;
		q.push(make_pair(rowIndex, colIndex));
		visitied[rowIndex][colIndex] = true;
		while (!q.empty())
		{
			++d;
			int size = q.size();
			for (int i=0;i<size;++i)
			{
				pair<int, int> cur = q.front();
				q.pop();
				for (int j = 0;j < 4;++j) {
					int rr = rowDir[j] + cur.first;
					int cc = colDir[j] + cur.second;
					if (!isValid(grid, rr, cc, visitied))continue;
					visitied[rr][cc] = true;
					q.push(make_pair(rr, cc));
					distance[rr][cc] += d;
					++canReach[rr][cc];
				}
			}
		}

	}
public:
	int shortestDistance(vector<vector<int>>&grid) {
		int rows = grid.size(), cols = grid[0].size();
		if (rows==0||cols==0)
		{
			return -1;
		}
		int minDis = INT_MAX;
		vector<vector<int>>canReach(rows, vector<int>(cols, 0));
		vector<vector<int>>distance(rows, vector<int>(cols, 0));
		int totalBuilding = 0;
		for(int i=0;i<rows;++i){
			for (int j = 0;j < cols;++j) {
				if (grid[i][j] == 1) {
					totalBuilding++;
					bfs(grid,distance,canReach,i,j);
				}
			}
		}
		for (int i = 0;i < rows;++i) {
			for (int j = 0;j < cols;++j) {
				if (canReach[i][j]==totalBuilding)
				{
					minDis = min(minDis, distance[i][j]);
				}
			}
		}
		return minDis == INT_MAX ? -1 : minDis;
	}

};
//字符串的排列
//输入一个字符串，打印出该字符串中字符的所有排列。
//你可以以任意顺序返回这个字符串数组，但里面不能有重复元素
class PermutarionString {
public:
	vector<string>ret;

	vector<string> permutation(string s) {

		helper(0, s);
		return ret;
	}
	void helper(int x, string &s) {
		if (x == s.size() - 1) {
			ret.push_back(s);
			return;
		}
		set<char>se;
		for (int i = x;i < s.size();++i) {
			if (se.find(s[i]) != se.end())
				continue;
			se.insert(s[i]);
			swap(i, x, s);
			helper(x + 1, s);
			swap(i, x, s);
		}
	}

	void swap(int x, int y, string &s) {
		char tem = s[x];
		s[x] = s[y];
		s[y] = tem;
	}

};
//131. 分割回文串
//给你一个字符串 s，请你将 s 分割成一些子串，使每个子串都是 回文串 。返回 s 所有可能的分割方案。
//
//回文串 是正着读和反着读都一样的字符串
class Partition {
public:
	vector<vector<string>>res;
	vector<string>cur;
	vector<vector<bool>>dp;
	vector<vector<string>> partition(string s) {
		int n = s.size();
		dp.assign(n, vector<bool>(n, true));
		for (int i = n - 1;i >= 0;--i) {
			for (int j = i + 1;j < n;++j) {
				dp[i][j] = dp[i + 1][j - 1] && s[i] == s[j];
			}
		}
		helper(0, s);

		return res;
	}
	//用dp预处理，dp[i][j]表示s[i]~s[j]的字符串是否为回文串
	void helper(int ind, string s) {
		if (ind == s.size()) {
			res.push_back(cur);
			return;
		}
		for (int i = ind;i < s.size();++i) {
			if (dp[ind][i]) {
				cur.push_back(s.substr(ind, i - ind + 1));
				helper(i + 1, s);
				cur.pop_back();
			}
		}
	}
	
	/*bool isPalindrome(string s, int i, int j) {
		while (i <= j) {
			if (s[i++] != s[j--])
				return false;
		}                                                          
		return true;
	}
	void helper(int ind, string s) {
		if (ind == s.size()) {
			res.push_back(cur);
			return;
		}
		for (int i = ind;i < s.size();++i) {
			if (isPalindrome(s, ind, i)) {
				cur.push_back(s.substr(ind, i - ind + 1));
				helper(i + 1, s);
				cur.pop_back();
			}
		}
	}*/
};
//46. Permutations
//Medium
//Given an array nums of distinct integers, return all the possible permutations.
//You can return the answer in any order.
class Permute {
public:
	vector<int>visitied;
	vector<vector<int>> permute(vector<int>& nums) {
		visitied.resize(nums.size());
		vector<vector<int>>res;
		vector<int>cur;
		backTrack(nums, cur, res);
		return res;
	}

	void backTrack(vector<int>& nums, vector<int>&cur, vector<vector<int>>&res) {
		if (cur.size() == nums.size()) {
			res.push_back(cur);return;
		}
		for (int i = 0;i < nums.size();++i) {
			if (visitied[i])continue;
			visitied[i] = true;
			cur.push_back(nums[i]);
			backTrack(nums, cur, res);
			visitied[i] = false;
			cur.pop_back();
		}
	}
};
//47. Permutations II
//Medium
//Given a collection of numbers, nums, that might contain duplicates, 
//return all possible unique permutations in any order.
class PermuteUnique {
public:
	vector<bool>visitied;
	vector<vector<int>> permuteUnique(vector<int>& nums) {
		sort(nums.begin(), nums.end());
		vector<vector<int>>res;
		vector<int>cur;
		visitied.resize(nums.size());
		backTrack(res, cur, nums);
		return res;
	}

	void backTrack(vector<vector<int>>&res, vector<int>&cur, vector<int>& nums) {
		if (cur.size() == nums.size()) {
			res.push_back(cur);return;
		}
		for (int i = 0;i < nums.size();++i) {
			if (visitied[i])continue;
			if (i > 0 && nums[i] == nums[i - 1] && !visitied[i - 1])continue;
			visitied[i] = true;
			cur.push_back(nums[i]);
			backTrack(res, cur, nums);
			visitied[i] = false;
			cur.pop_back();
		}
	}
};
//77. Combinations
//Medium
//Given two integers n and k, return all possible combinations of k numbers out of the range[1, n].
//
//You may return the answer in any order.
class Combine{
public:
	vector<vector<int>> combine(int n, int k) {
		vector<vector<int>> res;
		vector<int>cur;
		helper(res, cur, n, k, 1);
		return res;
	}

	void helper(vector<vector<int>> &res, vector<int>&cur, int n, int k, int id) {
		if (k == 0) {
			res.push_back(cur);return;
		}
		for (int i = id;i <= n;++i) {
			cur.push_back(i);
			helper(res, cur, n, k - 1, i + 1);
			cur.pop_back();
		}
	}
};
//39. Combination Sum
//Medium
//
//Given an array of distinct integers candidates and a target integer target, return a list of all unique combinations of candidates where the chosen numbers sum to target.You may return the combinations in any order.
//
//The same number may be chosen from candidates an unlimited number of times.Two combinations are unique if the frequency of at least one of the chosen numbers is different.
//
//It is guaranteed that the number of unique combinations that sum up to target is less than 150 combinations for the given input.
class CombinationSum {
public:

	vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
		vector<vector<int>> res;
		vector<int>cur;

		helper(candidates, res, cur, target, 0);
		return res;
	}

	void helper(vector<int>& candidates, vector<vector<int>> &res, vector<int>&cur, int target, int id) {
		if (target < 0)return;
		if (target == 0) {
			res.push_back(cur);return;
		}
		for (int i = id;i < candidates.size();++i) {
			cur.push_back(candidates[i]);
			helper(candidates, res, cur, target - candidates[i], i);
			cur.pop_back();
		}

	}
};
//40. Combination Sum II
//Medium
//Given a collection of candidate numbers(candidates) and a target number(target), find all unique combinations in candidates where the candidate numbers sum to target.
//
//Each number in candidates may only be used once in the combination.
//
//Note: The solution set must not contain duplicate combinations.
class CombinationSum2 {
public:

	vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
		vector<vector<int>> res;
		vector<int>cur;
		sort(candidates.begin(), candidates.end());

		helper(candidates, res, cur, target, 0);
		return res;
	}

	void helper(vector<int>& candidates, vector<vector<int>> &res, vector<int>&cur, int target, int id) {
		if (target < 0)return;
		if (target == 0) {
			res.push_back(cur);return;
		}

		for (int i = id;i < candidates.size();++i) {

			if (i > id&&candidates[i] == candidates[i - 1])continue;

			cur.push_back(candidates[i]);
			helper(candidates, res, cur, target - candidates[i], i + 1);
			cur.pop_back();

		}

	}
};
//216. Combination Sum III
//Medium
//
//Find all valid combinations of k numbers that sum up to n such that the following conditions are true:
//
//Only numbers 1 through 9 are used.
//Each number is used at most once.
//Return a list of all possible valid combinations.The list must not contain the same combination twice, and the combinations may be returned in any order.
class CombinationSum3 {
public:
	vector<vector<int>> combinationSum3(int k, int target) {
		vector<vector<int>> res;
		vector<int>cur;

		helper(k, res, cur, target, 1);
		return res;
	}

	void helper(int k, vector<vector<int>> &res, vector<int>&cur, int target, int id) {
		if (target < 0 || k < 0)return;
		if (target == 0 && k == 0) {
			res.push_back(cur);return;
		}

		for (int i = id;i < 10;++i) {
			cur.push_back(i);
			helper(k - 1, res, cur, target - i, i + 1);
			cur.pop_back();
		}
	}
};