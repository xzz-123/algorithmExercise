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
