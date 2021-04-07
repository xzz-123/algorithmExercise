#pragma once
#include <vector>
using namespace std;
class Hanota {
public:
	void move(int n, vector<int>&a, vector<int>&b, vector<int>&c) {
		if (n <= 0)return;
		if (n == 1) {
			c.push_back(a.back());
			a.pop_back();
			return;
		}
		move(n - 1, a, c, b);

		c.push_back(a.back());
		a.pop_back();
		move(n - 1, b, a, c);
	}
	void hanota(vector<int>& A, vector<int>& B, vector<int>& C) {
		int n = A.size();
		move(n, A, B, C);
	}
};
