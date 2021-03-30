#include <vector>
#include<algorithm>
using namespace std;
//剪绳子
//给你一根长度为 n 的绳子，请把绳子剪成整数长度的 m 段（m、n都是整数，n>1并且m>1），每段绳子的长度记为 k[0],k[1]...k[m-1] 。请问 k[0]*k[1]*...*k[m-1] 
//可能的最大乘积是多少？
class CutRope {
public:
	int cuttingRope(int n) {
		vector<int>dp(n + 1);
		dp[2] = 1;
		for (int i = 3;i < n + 1;++i) {
			for (int j = 2;j < i;++j) {
				dp[i] = max(dp[i], max(j*(i - j), j*dp[i - j]));
			}
		}
		return dp[n];
	}
};
//股票的最大利润
class MaxProfit {
public:
	int maxProfit(vector<int>& prices) {
		int minPrice = INT_MAX, ret = 0;
		for (auto &p : prices) {
			ret = max(ret, p - minPrice);
			minPrice = min(minPrice, p);
		}
		return ret;
	}
};