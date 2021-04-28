#pragma once
#include <vector>
#include <algorithm>
#include <numeric>
#include <set>
#include <queue>
#include <stack>
using namespace std;
//207. �γ̱�
//�����ѧ�ڱ���ѡ�� numCourses �ſγ̣���Ϊ 0 �� numCourses - 1 ��
//
//��ѡ��ĳЩ�γ�֮ǰ��ҪһЩ���޿γ̡� ���޿γ̰����� prerequisites ���������� prerequisites[i] = [ai, bi] ����ʾ���Ҫѧϰ�γ� ai �� ���� ��ѧϰ�γ�  bi ��
//
//���磬���޿γ̶�[0, 1] ��ʾ����Ҫѧϰ�γ� 0 ������Ҫ����ɿγ� 1 ��
//�����ж��Ƿ����������пγ̵�ѧϰ��������ԣ����� true �����򣬷��� false ��
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
//210. �γ̱� II
//�������ܹ��� n �ſ���Ҫѡ����Ϊ 0 �� n - 1��
//
//��ѡ��ĳЩ�γ�֮ǰ��ҪһЩ���޿γ̡� ���磬��Ҫѧϰ�γ� 0 ������Ҫ����ɿγ� 1 ��������һ��ƥ������ʾ����: [0, 1]
//
//�����γ������Լ����ǵ��Ⱦ�������������Ϊ��ѧ�����пγ������ŵ�ѧϰ˳��
//
//���ܻ��ж����ȷ��˳����ֻҪ����һ�־Ϳ����ˡ����������������пγ̣�����һ��������
class FindOrder2 {
public:
	bool hasCircle = false;
	stack<int>s;
	vector<vector<int>>adj;
	vector<int>state;
	vector<int> findOrder(int num, vector<vector<int>>& prerequisites) {
		adj.assign(num, vector<int>());
		state.assign(num, 0);
		//����ģ���ڽ�����
		for (auto i : prerequisites) {
			adj[i[1]].push_back(i[0]);
		}
		//ѡȡû�з��ʹ��Ľ�����dfs
		for (int i = 0;i < num;++i) {
			if (state[i] == 0)dfs(i);
		}
		//����л���ôû����������
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

//128. ���������
//����һ��δ������������� nums ���ҳ���������������У���Ҫ������Ԫ����ԭ�������������ĳ��ȡ�

//���ף��������Ʋ�ʵ��ʱ�临�Ӷ�Ϊ O(n) �Ľ��������
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
//���鼯
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
//�ⷨ1 ���鼯
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
//�ⷨ2 dfs
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
//399. ������ֵ
//����һ������������ equations ��һ��ʵ��ֵ���� values ��Ϊ��֪���������� equations[i] = [Ai, Bi] �� values[i] ��ͬ��ʾ��ʽ Ai / Bi = values[i] ��ÿ�� Ai �� Bi ��һ����ʾ�����������ַ�����
//
//����һЩ������ queries ��ʾ�����⣬���� queries[j] = [Cj, Dj] ��ʾ�� j �����⣬���������֪�����ҳ� Cj / Dj = ? �Ľ����Ϊ�𰸡�
//
//���� ��������Ĵ� ���������ĳ���޷�ȷ���Ĵ𰸣����� - 1.0 �������𰸡���������г����˸�������֪������û�г��ֵ��ַ�����Ҳ��Ҫ�� - 1.0 �������𰸡�
//
//ע�⣺����������Ч�ġ�����Լ�����������в�����ֳ���Ϊ 0 ��������Ҳ������κ�ì�ܵĽ����
//�ⷨ1��dfs
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
//�ⷨ2��bfs
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
//�ⷨ3�����鼯
class CalcEquation2 {
public:

	unordered_map<string, int>m;
	int count = 0;
	vector<int>fa;
	vector<double>weight;
	vector<double> calcEquation(vector<vector<string>>& equations, vector<double>& values, vector<vector<string>>& queries) {
		int n = equations.size();
		//��ÿ���ַ������
		for (auto vec : equations) {
			for (auto s : vec) {
				if (m.find(s) == m.end())m[s] = count++;
			}
		}
		fa.resize(count);
		weight.resize(count);
		//��ʼ�����׽ڵ��Ȩ��
		for (int i = 0;i < count;++i) {
			fa[i] = i;
			weight[i] = 1;
		}
		//����
		for (int i = 0;i < n;++i) {
			auto vec = equations[i];
			int a = m[vec[0]], b = m[vec[1]];
			Union(a, b, values[i]);
		}
		//����
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
	//���ҹ����г���·��ѹ������Ҫά��Ȩֵ��
	int find(int x) {
		if (x == fa[x])return x;
		else {
			//������������
			int origin = fa[x];
			//�ݹ�Ѱ�Ҹ��ڵ�
			fa[x] = find(fa[x]);
			//�ڷ��صĹ����У��Ӹ��ڵ�ĵ�һ�����ӿ�ʼ�������Ȩֵ
			weight[x] *= weight[origin];
			return fa[x];
		}
	}
	void Union(int a, int b, double value) {
		int x = find(a), y = find(b);
		if (x == y)return;
		fa[x] = y;
		//��һ��a�ĸ�x����b�ĸ�y��������ô��Ҫ����x��y��Ȩֵweight[x]
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
	//�ⷨ1�����鼯
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
	//�ⷨ2��dfs
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
//684. ��������
//�ڱ�������, ��ָ����һ����ͨ���޻�������ͼ��
//
//����һ��ͼ����ͼ��һ������N���ڵ�(�ڵ�ֵ���ظ�1, 2, ..., N) ������һ�����ӵı߹��ɡ����ӵıߵ��������������1��N�м䣬�������ӵı߲����������Ѵ��ڵıߡ�
//
//���ͼ��һ���Ա���ɵĶ�ά���顣ÿһ���ߵ�Ԫ����һ��[u, v] ������ u < v����ʾ���Ӷ���u ��v������ͼ�ıߡ�
//
//	����һ������ɾȥ�ıߣ�ʹ�ý��ͼ��һ������N���ڵ����������ж���𰸣��򷵻ض�ά�����������ֵıߡ��𰸱�[u, v] Ӧ������ͬ�ĸ�ʽ u < v
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
//�ڱ������У��и���ָ������������������ͼ��1������ֻ��һ�����ڵ㣬���������ڵ㶼�Ǹø��ڵ�ĺ�̡���2��ÿһ���ڵ�ֻ��һ�����ڵ㣬���˸��ڵ�û�и��ڵ㡣
//����һ������ͼ����ͼ��һ������ N ���ڵ�(�ڵ�ֵ���ظ�1, 2, ��, N) ������һ�����ӵı߹��ɡ����ӵıߵ��������������1��N�м䣬�������ӵı߲����������Ѵ���
//�ıߡ����ͼ��һ���Ա���ɵĶ�ά���顣 ÿһ���ߵ�Ԫ����һ��[u, v]�����Ա�ʾ����ͼ�����Ӷ��� u and v �Ͷ���ıߣ�
//���и��ڵ� u ���ӽڵ� v ��һ�����ڵ㡣����һ����ɾ���ıߣ�ʹ��ʣ�µ�ͼ���� N ���ڵ���и��������ж���𰸣������������ڸ�����ά����Ĵ𰸡�

//�������684���������ڣ�684������ߣ�1��ʹ����ͼ���л�
//685������������������1��ʹ����ͼ�л���2��ʹĳ���ڵ����������׽ڵ�
//����˼·����1���ȱ���һ�飬����нڵ����������׽ڵ㣬��ô��¼ʹ�����������׽ڵ�������ߣ��𰸱�����������֮�У���Ϊ�����������ߣ���ô�õ������ߺ�����ͼ��
//����ڵ㻹�����������׽ڵ㣬�������и����������������Ѻ�������������Ϊ��ѡ��1������һ����Ϊ��ѡ��2�����Ժ�ѡ��1������ǡ�������нڵ㶼ֻ��һ�����ڵ㣨����
//���ڵ㣩����ôֱ���ڵڶ������ҵ�ʹͼ�γɻ��ı߾��Ǵ�
//��2����ʼ�ϲ��ڵ㣬�ϲ�������������ѡ��1������������ϲ��������л���˵������ѡ���˴���ĺ�ѡ�ˣ����Ƿ��غ�ѡ��2����֮�����һֱ�����û���ֻ�����ôѡ����
//���غ�ѡ��1
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
			//�л�
			if (fx == fy) {
				if (!can2.empty())return can2;
				else return edge;
			}
			//û���������ϲ�
			fa[y] = fx;
		}
		return can1;
	}

};
//1091. Shortest Path in Binary Matrix(Medium)
//��Ŀ������0 ��ʾ���Ծ���ĳ��λ�ã��������Ͻǵ����½ǵ����·�����ȡ�
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
//417. ̫ƽ�������ˮ������
//����һ�� m x n �ķǸ�������������ʾһƬ��½�ϸ�����Ԫ��ĸ߶ȡ���̫ƽ�󡱴��ڴ�½����߽���ϱ߽磬���������󡱴��ڴ�½���ұ߽���±߽硣
//
//�涨ˮ��ֻ�ܰ����ϡ��¡������ĸ�������������ֻ�ܴӸߵ��ͻ�����ͬ�ȸ߶���������
//
//���ҳ���Щˮ���ȿ�����������̫ƽ�󡱣������������������󡱵�½�ص�Ԫ�����ꡣ
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