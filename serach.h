#pragma once
#include <algorithm>
#include <vector>
#include <utility>
using namespace std;
class RobotMoveCount {
public:
	int rowDir[2] = { 0,1 };
	int colDir[2] = { 1,0 };

	int movingCount(int m, int n, int k) {
		int ans = 1;
		vector<vector<bool>>visitied(m, vector<bool>(n, false));
		queue<pair<int, int>>q;
		q.push(make_pair(0, 0));
		visitied[0][0] = 1;
		while (!q.empty()) {
			pair<int,int> cur= q.front();
			int x = cur.first, y = cur.second;
			q.pop();

			for (int i = 0;i < 2;++i) {
				int rr = x + rowDir[i], cc = y + colDir[i];
				if (rr >= m || rr < 0 || cc < 0 || cc >= n || visitied[rr][cc] || !isValid(rr, cc, k))continue;
				visitied[rr][cc] = true;
				++ans;
				q.push(make_pair(rr, cc));
			}
		}
		return ans;
	}

	bool isValid(int m, int n, int k) {
		int sum = 0;
		while (m != 0) {
			sum += m % 10;
			m /= 10;
		}
		while (n != 0) {
			sum += n % 10;
			n /= 10;
		}
		return sum <= k;
	}
};
//695. Max Area of Island
//Medium
//
//Given a non - empty 2D array grid of 0's and 1's, an island is a group of 1's (representing land) connected 4-directionally (horizontal or vertical.) You may assume all four edges of the grid are surrounded by water.
//
//Find the maximum area of an island in the given 2D array. (If there is no island, the maximum area is 0.)
class MaxAreaOfIsland {
public:
	int res = 0;
	int rowD[4] = { 0,0,1,-1 };
	int colD[4] = { 1,-1,0,0 };
	int maxAreaOfIsland(vector<vector<int>>& grid) {
		int rows = grid.size(), cols = grid[0].size();
		vector<vector<int>> visitied(rows, vector<int>(cols));
		for (int i = 0;i < rows;++i) {
			for (int j = 0;j < cols;++j) {
				res = max(res, dfs(grid, visitied, i, j));
			}
		}
		return res;
	}

	int dfs(vector<vector<int>>& grid, vector<vector<int>>& visitied, int x, int y) {
		if (x < 0 || x >= grid.size() || y < 0 || y >= grid[0].size() || grid[x][y] == 0 || visitied[x][y])return 0;
		int ret = 1;
		visitied[x][y] = 1;
		for (int i = 0;i < 4;++i) {
			ret += dfs(grid, visitied, x + rowD[i], y + colD[i]);
		}
		return ret;
	}
};

//200. Number of Islands
//Medium
//Given an m x n 2D binary grid grid which represents a map of '1's(land) and '0's(water), return the number of islands.

//An island is surrounded by water and is formed by connecting adjacent lands horizontally or vertically.
//You may assume all four edges of the grid are all surrounded by water.
class NumIslands {
public:
	int rowD[4] = { 0,0,1,-1 };
	int colD[4] = { 1,-1,0,0 };
	int numIslands(vector<vector<char>>& grid) {
		int rows = grid.size(), cols = grid[0].size();
		int res = 0;
		for (int i = 0;i < rows;++i) {
			for (int j = 0;j < cols;++j) {
				if (grid[i][j] == '1') {
					dfs(grid, i, j);
					++res;
				}
			}
		}
		return res;
	}

	void dfs(vector<vector<char>>& grid, int x, int y) {
		if (x < 0 || x >= grid.size() || y < 0 || y >= grid[0].size() || grid[x][y] == '0')return;
		grid[x][y] = '0';
		for (int i = 0;i < 4;++i) {
			dfs(grid, x + rowD[i], y + colD[i]);
		}
	}
};

//1254. Number of Closed Islands
//Medium
//Given a 2D grid consists of 0s(land) and 1s(water).An island is a maximal 4 - directionally connected group of 0s and a closed island is an island totally(all left, top, right, bottom) surrounded by 1s.
//
//Return the number of closed islands.


class ClosedIsland {
public:
	int rowD[4] = { 0,0,1,-1 };
	int colD[4] = { 1,-1,0,0 };
	int closedIsland(vector<vector<int>>& grid) {
		int rows = grid.size(), cols = grid[0].size();
		for (int i = 0;i < cols;++i) {
			dfs(grid, 0, i);
			dfs(grid, rows - 1, i);
		}
		for (int i = 0;i < rows;++i) {
			dfs(grid, i, 0);
			dfs(grid, i, cols - 1);
		}
		int res = 0;
		for (int i = 0;i < rows;++i) {
			for (int j = 0;j < cols;++j) {
				if (grid[i][j] == 0) {
					dfs(grid, i, j);
					++res;
				}
			}
		}
		return res;
	}

	void dfs(vector<vector<int>>& grid, int x, int y) {
		if (x < 0 || x >= grid.size() || y < 0 || y >= grid[0].size() || grid[x][y] == 1)return;
		grid[x][y] = 1;
		for (int i = 0;i < 4;++i) {
			dfs(grid, x + rowD[i], y + colD[i]);
		}
	}
};
//93. Restore IP Addresses
//Medium
//
//Given a string s containing only digits, return all possible valid IP addresses that can be obtained from s.You can return them in any order.
//
//A valid IP address consists of exactly four integers, each integer is between 0 and 255, 
//separated by single dots and cannot have leading zeros.For example, "0.1.2.201" and "192.168.1.1" are valid IP addresses and "0.011.255.245", "192.168.1.312" and "192.168@1.1" are invalid IP addresses.
class RestoreIpAddresses {
public:
	vector<string> restoreIpAddresses(string s) {
		vector<string>res;
		string cur = "";
		dfs(res, s, cur, 0, 0);
		return res;
	}
	void dfs(vector<string>&res, string &s, string cur, int id, int seg) {
		if (id>=s.size()||seg==4)
		{
			if (id == s.size() && seg == 4) {
				res.push_back(cur);
			}
			return;
		}
		
		if (s[id] == '0') {
			dfs(res, s, cur + (seg == 3 ? "0" : "0."), id + 1, seg + 1);
		}
		else {
			string subs;
			for (int i = 1;i <= 3;++i) {
				subs = s.substr(id, i);
				if (stoi(subs) > 255)continue;
				dfs(res, s, cur + subs + (seg == 3 ? "" : "."), id + i, seg + 1);
			}
		}
	}
};

