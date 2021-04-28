#pragma once
#include <vector>
#include <algorithm>
#include <numeric>
#include <set>
#include <queue>
#include <stack>
using namespace std;
//207. 课程表
//你这个学期必须选修 numCourses 门课程，记为 0 到 numCourses - 1 。
//
//在选修某些课程之前需要一些先修课程。 先修课程按数组 prerequisites 给出，其中 prerequisites[i] = [ai, bi] ，表示如果要学习课程 ai 则 必须 先学习课程  bi 。
//
//例如，先修课程对[0, 1] 表示：想要学习课程 0 ，你需要先完成课程 1 。
//请你判断是否可能完成所有课程的学习？如果可以，返回 true ；否则，返回 false 。
class FindOrder {
public:
	vector<int> findOrder(int num, vector<vector<int>>& prerequisites) {
		vector<vector<int>>adj(num);
		vector<int> indegree(num);
		for (auto i : prerequisites) {
			adj[i[1]].push_back(i[0]);
			indegree[i[0]]++;
		}

		queue<int>q;
		for (int i = 0;i < num;++i) {
			if (indegree[i] == 0)
				q.push(i);
		}
		vector<int>res;
		int count = 0;
		while (!q.empty()) {
			int cur = q.front();
			q.pop();
			++count;
			res.push_back(cur);
			for (auto v : adj[cur]) {
				if (--indegree[v] == 0)q.push(v);
			}
		}
		if (count == num)
			return res;
		else return vector<int>();
	}
};
//210. 课程表 II
//现在你总共有 n 门课需要选，记为 0 到 n - 1。
//
//在选修某些课程之前需要一些先修课程。 例如，想要学习课程 0 ，你需要先完成课程 1 ，我们用一个匹配来表示他们: [0, 1]
//
//给定课程总量以及它们的先决条件，返回你为了学完所有课程所安排的学习顺序。
//
//可能会有多个正确的顺序，你只要返回一种就可以了。如果不可能完成所有课程，返回一个空数组
class FindOrder2 {
public:
	bool hasCircle = false;
	stack<int>s;
	vector<vector<int>>adj;
	vector<int>state;
	vector<int> findOrder(int num, vector<vector<int>>& prerequisites) {
		adj.assign(num, vector<int>());
		state.assign(num, 0);
		//数组模拟邻接链表
		for (auto i : prerequisites) {
			adj[i[1]].push_back(i[0]);
		}
		//选取没有访问过的结点进行dfs
		for (int i = 0;i < num;++i) {
			if (state[i] == 0)dfs(i);
		}
		//如果有环那么没有拓扑排序
		if (hasCircle)return vector<int>();
		vector<int>res;
		while (!s.empty()) {
			res.push_back(s.top());
			s.pop();
		}
		return res;
	}
	void dfs(int u) {
		state[u] = 1;
		for (auto v : adj[u]) {
			if (state[v] == 0) {
				dfs(v);
				if (hasCircle)return;
			}
			else if (state[v] == 1) {
				hasCircle = true;
				return;
			}
		}
		s.push(u);
		state[u] = 2;
	}
};

//128. 最长连续序列
//给定一个未排序的整数数组 nums ，找出数字连续的最长序列（不要求序列元素在原数组中连续）的长度。

//进阶：你可以设计并实现时间复杂度为 O(n) 的解决方案吗
class LongestConsecutive {
public:
	int longestConsecutive(vector<int>& nums) {
		unordered_set<int>s(nums.begin(), nums.end());
		int longest = 0;
		for (int num : nums) {
			if (s.find(num - 1) != s.end())continue;
			int cur = 1;
			while (s.find(1 + num++) != s.end())++cur;
			longest = max(longest, cur);
		}
		return longest;
	}
};
//并查集
class LongestConsecutive1 {
public:
	vector<int>fa;
	int find(int x) {
		return x == fa[x] ? x : find(fa[x]);
	}

	void Union(int x, int y) {
		int f1 = find(x), f2 = find(y);
		fa[f1] = f2;
	}
	int longestConsecutive(vector<int>& num) {
		int res = 0;
		unordered_map<int, int>m;
		int n = num.size();
		fa.resize(n);
		for (int i = 0;i < n;++i) {
			fa[i] = i;
		}
		for (int i = 0;i < n;++i) {
			if (m.find(num[i]) != m.end())continue;
			if (m.find(num[i] - 1) != m.end())Union(m[num[i] - 1], i);
			if (m.find(num[i] + 1) != m.end())Union(m[num[i] + 1], i);
			m[num[i]] = i;
		}

		vector<int>count(n);
		for (int i = 0;i < n;++i) {
			count[find(i)]++;
			res = max(res, count[find(i)]);
		}
		return res;
	}
};
//130. Surrounded Regions
//Medium
//Share
//Given an m x n matrix board containing 'X' and 'O', capture all regions surrounded by 'X'.
//
//A region is captured by flipping all 'O's into 'X's in that surrounded region.
//解法1 并查集
class Surrounded {
public:
	int rowD[4] = { 0,0,1,-1 };
	int colD[4] = { 1,-1,0,0 };
	vector<int>fa;
	void Union(int a, int b) {
		int x = find(a), y = find(b);
		fa[x] = y;
	}
	int find(int a) {
		return a == fa[a] ? a : find(fa[a]);
	}
	void solve(vector<vector<char>>& board) {
		int rows = board.size(), cols = board[0].size();
		fa.resize(rows*cols + 1);
		for (int i = 0;i < rows;++i) {
			for (int j = 0;j < cols;++j) {
				fa[i*cols + j] = i * cols + j;
			}
		}
		for (int i = 0;i < rows;++i) {
			for (int j = 0;j < cols;++j) {
				if (board[i][j] == 'X')continue;
				if (i == 0 || i == rows - 1 || j == 0 || j == cols - 1)
					Union(rows*cols, i*cols + j);
				else {
					for (int k = 0;k < 4;++k) {
						int rr = i + rowD[k], cc = j + colD[k];
						if (rr >= 0 && rr < rows&&cc >= 0 && cc < cols&&board[rr][cc] == 'O')
							Union(rr*cols + cc, i*cols + j);
					}
				}

			}
		}

		for (int i = 0;i < rows;++i) {
			for (int j = 0;j < cols;++j) {
				if (board[i][j] == 'X')continue;
				if (find(i*cols + j) != find(rows*cols))board[i][j] = 'X';
			}
		}
	}
};
//解法2 dfs
class Surrounded1 {
public:
	int rowD[4] = { 0,0,1,-1 };
	int colD[4] = { 1,-1,0,0 };
	void dfs(vector<vector<char>>&board, int x, int y) {
		if (x < 0 || x >= board.size() || y < 0 || y >= board[0].size() || board[x][y] != 'O')
			return;
		board[x][y] = '#';
		for (int i = 0;i < 4;++i) {
			dfs(board, x + rowD[i], y + colD[i]);
		}
	}
	void solve(vector<vector<char>>& board) {
		int rows = board.size(), cols = board[0].size();

		for (int i = 0;i < rows;++i) {
			dfs(board, i, 0);
			dfs(board, i, cols - 1);
		}
		for (int i = 0;i < cols;++i) {
			dfs(board, 0, i);
			dfs(board, rows - 1, i);
		}
		for (int i = 0;i < rows;++i) {
			for (int j = 0;j < cols;++j) {
				if (board[i][j] == 'O')board[i][j] = 'X';
				else if (board[i][j] == '#')board[i][j] = 'O';
			}
		}
	}
};
//399. 除法求值
//给你一个变量对数组 equations 和一个实数值数组 values 作为已知条件，其中 equations[i] = [Ai, Bi] 和 values[i] 共同表示等式 Ai / Bi = values[i] 。每个 Ai 或 Bi 是一个表示单个变量的字符串。
//
//另有一些以数组 queries 表示的问题，其中 queries[j] = [Cj, Dj] 表示第 j 个问题，请你根据已知条件找出 Cj / Dj = ? 的结果作为答案。
//
//返回 所有问题的答案 。如果存在某个无法确定的答案，则用 - 1.0 替代这个答案。如果问题中出现了给定的已知条件中没有出现的字符串，也需要用 - 1.0 替代这个答案。
//
//注意：输入总是有效的。你可以假设除法运算中不会出现除数为 0 的情况，且不存在任何矛盾的结果。
//解法1，dfs
class CalcEquation {
public:
	vector<bool>visitied;
	vector<double> calcEquation(vector<vector<string>>& equations, vector<double>& values, vector<vector<string>>& queries) {
		int n = equations.size();
		vector<vector<double>>graph = buildGraph(equations, values);
		vector<double>res;
		for (auto vec : queries) {
			visitied.assign(count, false);
			if (m.find(vec[0]) == m.end() || m.find(vec[1]) == m.end())
				res.push_back(-1.0);
			else {
				double prod = dfs(m[vec[1]], m[vec[0]], 1, graph);
				res.push_back(prod);
			}
		}
		return res;
	}
	unordered_map<string, int>m;
	int count = 0;
	vector<vector<double>> buildGraph(vector<vector<string>>& equations, vector<double>& values) {
		for (int i = 0;i < equations.size();++i) {
			string start = equations[i][1], end = equations[i][0];
			if (m.find(start) == m.end())m[start] = count++;
			if (m.find(end) == m.end())m[end] = count++;
		}
		visitied.resize(count);
		vector<vector<double>>graph(count, vector<double>(count, INT_MAX));
		for (int i = 0;i < equations.size();++i) {
			string start = equations[i][1], end = equations[i][0];
			graph[m[start]][m[end]] = values[i];
			graph[m[end]][m[start]] = 1.0 / values[i];
		}
		return graph;
	}

	double dfs(int start, int end, double cur, vector<vector<double>>&graph) {
		if (start == end)return cur;
		visitied[start] = true;
		for (int i = 0;i < graph[start].size();++i) {
			double u = graph[start][i];
			if (u != INT_MAX && !visitied[i]) {
				double prod = dfs(i, end, cur*u, graph);
				if (prod != -1.0)return prod;
			}
		}
		return -1.0;
	}
};
//解法2：bfs
class CalcEquation1 {
public:
	vector<bool>visitied;
	vector<double> calcEquation(vector<vector<string>>& equations, vector<double>& values, vector<vector<string>>& queries) {
		int n = equations.size();
		vector<vector<double>>graph = buildGraph(equations, values);
		vector<double>res;
		for (auto vec : queries) {
			visitied.assign(count, false);
			if (m.find(vec[0]) == m.end() || m.find(vec[1]) == m.end())
				res.push_back(-1.0);
			else {
				queue<int>q;
				q.push(m[vec[1]]);
				int target = m[vec[0]];
				vector<double>curProd(count, 1);
				bool find = false;
				while (!q.empty()) {
					int size = q.size();
					for (int i = 0;i < size;++i) {
						int cur = q.front();q.pop();
						visitied[cur] = true;
						if (cur == target) {
							res.push_back(curProd[cur]);find = true;break;
						}
						for (int j = 0;j < graph[cur].size();++j) {
							double dis = graph[cur][j];
							if (!visitied[j] && dis != INT_MAX) {
								q.push(j);
								curProd[j] = curProd[cur]*dis;
							}
						}
					}
					if(find)break;
				}
				if (!find)res.push_back(-1.0);
			}
		}
		return res;
	}
	unordered_map<string, int>m;
	int count = 0;
	vector<vector<double>> buildGraph(vector<vector<string>>& equations, vector<double>& values) {
		for (int i = 0;i < equations.size();++i) {
			string start = equations[i][1], end = equations[i][0];
			if (m.find(start) == m.end())m[start] = count++;
			if (m.find(end) == m.end())m[end] = count++;
		}
		visitied.resize(count);
		vector<vector<double>>graph(count, vector<double>(count, INT_MAX));
		for (int i = 0;i < equations.size();++i) {
			string start = equations[i][1], end = equations[i][0];
			graph[m[start]][m[end]] = values[i];
			graph[m[end]][m[start]] = 1.0 / values[i];
		}
		return graph;
	}

};
//解法3：并查集
class CalcEquation2 {
public:

	unordered_map<string, int>m;
	int count = 0;
	vector<int>fa;
	vector<double>weight;
	vector<double> calcEquation(vector<vector<string>>& equations, vector<double>& values, vector<vector<string>>& queries) {
		int n = equations.size();
		//给每个字符串编号
		for (auto vec : equations) {
			for (auto s : vec) {
				if (m.find(s) == m.end())m[s] = count++;
			}
		}
		fa.resize(count);
		weight.resize(count);
		//初始化父亲节点和权重
		for (int i = 0;i < count;++i) {
			fa[i] = i;
			weight[i] = 1;
		}
		//连接
		for (int i = 0;i < n;++i) {
			auto vec = equations[i];
			int a = m[vec[0]], b = m[vec[1]];
			Union(a, b, values[i]);
		}
		//查找
		vector<double>res;
		for (auto vec : queries) {
			if (m.find(vec[0]) == m.end() || m.find(vec[1]) == m.end())
				res.push_back(-1.0);
			else {
				int root1 = find(m[vec[0]]), root2 = find(m[vec[1]]);
				if (root1 != root2)res.push_back(-1.0);
				else res.push_back(weight[m[vec[0]]] / weight[m[vec[1]]]);
			}
		}
		return res;
	}
	//查找过程中除了路径压缩，还要维护权值。
	int find(int x) {
		if (x == fa[x])return x;
		else {
			//保存亲生父亲
			int origin = fa[x];
			//递归寻找根节点
			fa[x] = find(fa[x]);
			//在返回的过程中，从根节点的第一个儿子开始往后更新权值
			weight[x] *= weight[origin];
			return fa[x];
		}
	}
	void Union(int a, int b, double value) {
		int x = find(a), y = find(b);
		if (x == y)return;
		fa[x] = y;
		//上一行a的根x认了b的根y做爹，那么需要更新x到y的权值weight[x]
		weight[x] = weight[b] * value / weight[a];
	}
};
//547. Number of Provinces
//
//There are n cities.Some of them are connected, while some are not.If city a is connected directly with city b, and city b is connected directly with city c, then city a is connected indirectly with city c.
//
//A province is a group of directly or indirectly connected cities and no other cities outside of the group.
//
//You are given an n x n matrix isConnected where isConnected[i][j] = 1 if the ith city and the jth city are directly connected, and isConnected[i][j] = 0 otherwise.
//
//Return the total number of provinces

class UF {
public:
	vector<int>fa;
	vector<int>rank;
	UF(int size) {
		fa.resize(size);
		rank.resize(size);
		for (int i = 0;i < size;++i) {
			fa[i] = i;
			rank[i] = 1;
		}


	}

	int find(int x) {
		return x == fa[x] ? x : (fa[x] = find(fa[x]));
	}

	void  Union(int x, int y) {
		int r1 = find(x), r2 = find(y);
		if (r1 == r2)return;
		if (rank[r1] < rank[r2]) {
			fa[r1] = r2;
			rank[r2]++;
		}
		else {
			fa[r2] = r1;
			rank[r1]++;
		}
	}
};
class FindCircleNum {

public:
	//解法1，并查集
	int findCircleNum(vector<vector<int>>& isConnected) {
		int n = isConnected.size();
		UF uf(n);

		for (int i = 0;i < n;++i) {
			for (int j = 0;j < n;++j) {

				if (isConnected[i][j] == 1)uf.Union(i, j);
			}
		}
		unordered_set<int>ancestors;
		for (int i = 0;i < n;++i) {
			int r = uf.find(i);
			ancestors.insert(r);
		}
		return ancestors.size();

	}
	//解法2，dfs
	int findCircleNum1(vector<vector<int>>& isConnected) {
		int n = isConnected.size();
		vector<int>visitied(n);
		int res = 0;
		for (int i = 0;i < n;++i) {
			if (!visitied[i]) {
				dfs(isConnected, visitied, i);++res;
			}
		}
		return res;
	}

	void dfs(vector<vector<int>>& isConnected, vector<int>&visitied, int x) {
		if (x > isConnected.size() - 1 || visitied[x])return;
		visitied[x] = true;
		for (int i = 0;i < isConnected.size();++i) {
			if (isConnected[x][i] == 1)dfs(isConnected, visitied, i);
		}
	}
};
//684. 冗余连接
//在本问题中, 树指的是一个连通且无环的无向图。
//
//输入一个图，该图由一个有着N个节点(节点值不重复1, 2, ..., N) 的树及一条附加的边构成。附加的边的两个顶点包含在1到N中间，这条附加的边不属于树中已存在的边。
//
//结果图是一个以边组成的二维数组。每一个边的元素是一对[u, v] ，满足 u < v，表示连接顶点u 和v的无向图的边。
//
//	返回一条可以删去的边，使得结果图是一个有着N个节点的树。如果有多个答案，则返回二维数组中最后出现的边。答案边[u, v] 应满足相同的格式 u < v
class FindRedundantConnection {
public:
	vector<int>fa;
	int find(int x) {
		if (fa[x] == x)return x;
		else return fa[x] = find(fa[x]);
	}

	void Union(int x, int y) {
		fa[find(x)] = find(y);
	}

	vector<int> findRedundantConnection(vector<vector<int>>& edges) {
		int n = edges.size();
		fa.resize(n + 1);
		for (int i = 1;i <= n;++i) {
			fa[i] = i;
		}
		for (auto edge : edges) {
			int x = edge[0], y = edge[1];
			if (find(x) == find(y))return edge;
			else Union(x, y);
		}
		return vector<int>();
	}
};
//685.Redundant Connection II 
//在本问题中，有根树指满足以下条件的有向图（1）该树只有一个根节点，所有其他节点都是该根节点的后继。（2）每一个节点只有一个父节点，除了根节点没有父节点。
//输入一个有向图，该图由一个有着 N 个节点(节点值不重复1, 2, …, N) 的树及一条附加的边构成。附加的边的两个顶点包含在1到N中间，这条附加的边不属于树中已存在
//的边。结果图是一个以边组成的二维数组。 每一个边的元素是一对[u, v]，用以表示有向图中连接顶点 u and v 和顶点的边，
//其中父节点 u 是子节点 v 的一个父节点。返回一条能删除的边，使得剩下的图是有 N 个节点的有根树。若有多个答案，返回最后出现在给定二维数组的答案。

//这道题与684的区别在于，684中冗余边（1）使无向图中有环
//685中冗余边有两种情况（1）使有向图有环（2）使某个节点有两个父亲节点
//解题思路：（1）先遍历一遍，如果有节点有两个父亲节点，那么记录使他有两个父亲节点的两条边，答案必在这两条边之中（因为如果答案另有其边，那么拿掉那条边后，有向图中
//这个节点还是有两个父亲节点，不满足有根树的条件），并把后来的那条边作为候选边1，另外一条作为候选人2，并对候选人1做个标记。如果所有节点都只有一个父节点（除了
//根节点），那么直接在第二步中找到使图形成环的边就是答案
//（2）开始合并节点，合并过程中碰到候选人1就跳过，如果合并过程中有环，说明我们选择了错误的候选人，这是返回候选人2，反之，如果一直到最后都没出现环，那么选对了
//返回候选人1
class FindRedundantDirectedConnection {
public:

	vector<int>fa;
	int find(int x) {
		if (fa[x] == x)return x;
		else return find(fa[x]);
	}

	vector<int> findRedundantDirectedConnection(vector<vector<int>>& edges) {
		int n = edges.size();
		fa.resize(n + 1, 0);
		vector<int>can1, can2;
		for (auto &edge : edges) {
			int x = edge[0], y = edge[1];
			if (fa[y] == 0)fa[y] = x;
			else {
				can1 = edge;
				can2 = vector<int>{ fa[y],y };
				edge[1] = 0;
			}
		}
		for (int i = 1;i <= n;++i)fa[i] = i;
		for (auto edge : edges) {
			int x = edge[0], y = edge[1];
			if (y == 0)continue;
			int fx = find(x), fy = find(y);
			//有环
			if (fx == fy) {
				if (!can2.empty())return can2;
				else return edge;
			}
			//没环，继续合并
			fa[y] = fx;
		}
		return can1;
	}

};
//1091. Shortest Path in Binary Matrix(Medium)
//题目描述：0 表示可以经过某个位置，求解从左上角到右下角的最短路径长度。
class ShortestPathBinaryMatrix {
public:
	int rowD[8] = { 0,0,1,-1,1,-1,1,-1 };
	int colD[8] = { 1,-1,0,0,1,-1,-1,1 };
	int shortestPathBinaryMatrix(vector<vector<int>>& grid) {
		int row = grid.size(), col = grid[0].size();
		if (grid[0][0] == 1)return -1;
		queue<pair<int, int>>q;
		q.push(make_pair(0, 0));
		grid[0][0] = 1;
		int res = 0;
		while (!q.empty()) {
			int size = q.size();
			res++;
			for (int i = 0;i < size;++i) {
				auto pair = q.front();
				q.pop();
				if (pair.first == row - 1 && pair.second == col - 1)return res;
				for (int j = 0;j < 8;++j) {
					int rr = pair.first + rowD[j], cc = pair.second + colD[j];
					if (rr >= 0 && rr < row&&cc >= 0 && cc < col&&grid[rr][cc] == 0) {
						q.push(make_pair(rr, cc));
						grid[rr][cc] = 1;
					}
				}
			}

		}
		return -1;
	}
};
//127. Word Ladder
//A transformation sequence from word beginWord to word endWord using a dictionary wordList is a sequence of words beginWord->s1->s2 -> ...->sk such that :
//Every adjacent pair of words differs by a single letter.
//Every si for 1 <= i <= k is in wordList.Note that beginWord does not need to be in wordList.
//Given two words, beginWord and endWord, and a dictionary wordList, return the number of words in the shortest transformation sequence from beginWord to endWord, or 0 if no such sequence exists.
class LadderLength {
public:
	int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
		unordered_set<string>words(wordList.begin(), wordList.end());
		queue<string>q;
		q.push(beginWord);
		int len = wordList.size();
		int res = 0;
		while (!q.empty()) {
			int size = q.size();
			++res;
			for (int i = 0;i < size;++i) {
				string cur = q.front();
				q.pop();
				if (cur == endWord) {
					return res;
				}
				words.erase(cur);
				for (int j = 0;j < cur.size();++j) {
					char c = cur[j];
					for (int k = 0;k < 26;++k) {
						cur[j] = 'a' + k;
						if (words.find(cur) != words.end()) {
							q.push(cur);
						}
					}
					cur[j] = c;
				}
			}
		}
		return 0;
	}
};
//417. 太平洋大西洋水流问题
//给定一个 m x n 的非负整数矩阵来表示一片大陆上各个单元格的高度。“太平洋”处于大陆的左边界和上边界，而“大西洋”处于大陆的右边界和下边界。
//
//规定水流只能按照上、下、左、右四个方向流动，且只能从高到低或者在同等高度上流动。
//
//请找出那些水流既可以流动到“太平洋”，又能流动到“大西洋”的陆地单元的坐标。
class PacificAtlantic {
public:
	int rowD[4] = { 0,0,1,-1 };
	int colD[4] = { 1,-1,0,0 };
	vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights) {
		int rows = heights.size(), cols = heights[0].size();
		vector<vector<int>>canReachA(rows, vector<int>(cols));
		vector<vector<int>>canReachP(canReachA);
		for (int i = 0;i < cols;++i) {
			dfs(heights, 0, i, canReachP);
			dfs(heights, rows - 1, i, canReachA);
		}
		for (int i = 0;i < rows;++i) {
			dfs(heights, i, 0, canReachP);
			dfs(heights, i, cols - 1, canReachA);
		}
		vector<vector<int>>res;
		for (int i = 0;i < rows;++i) {
			for (int j = 0;j < cols;++j) {
				if (canReachP[i][j] && canReachA[i][j])
					res.push_back(vector<int>{i, j});
			}
		}
		return res;
	}

	void dfs(vector<vector<int>>& heights, int x, int y, vector<vector<int>>&canReach) {
		
		canReach[x][y] = 1;
		for (int i = 0;i < 4;++i) {
			int rr = x + rowD[i], cc = y + colD[i];
			if (rr < 0 || cc < 0 || rr >= heights.size() || cc >= heights[0].size() || canReach[rr][cc])continue;
			if (heights[x][y] <= heights[rr][cc])
				dfs(heights, rr, cc, canReach);
		}
	}
};