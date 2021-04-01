#pragma once
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;
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