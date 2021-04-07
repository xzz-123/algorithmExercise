#pragma once
#include <vector>
#include<algorithm>
#include <unordered_map>
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

//给定两个字符串 text1 和 text2，返回这两个字符串的最长 公共子序列 的长度。如果不存在 公共子序列 ，返回 0 。
//
//一个字符串的 子序列 是指这样一个新的字符串：它是由原字符串在不改变字符的相对顺序的情况下删除某些字符（也可以不删除任何字符）后组成的新字符串。
//
//例如，"ace" 是 "abcde" 的子序列，但 "aec" 不是 "abcde" 的子序列。
//两个字符串的 公共子序列 是这两个字符串所共同拥有的子序列。

class LongestCommonSubsequence {
public:
	int longestCommonSubsequence(string text1, string text2) {
		int M = text1.size(), N = text2.size();
		vector<vector<int>>dp(M + 1, vector<int>(N + 1, 0));
		for (int i = 1;i <= M;++i) {
			for (int j = 1;j <= N;++j) {
				if (text1[i - 1] == text2[j - 1])dp[i][j] = dp[i - 1][j - 1] + 1;
				else dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
			}
		}
		return dp[M][N];
	}
};
//给定两个字符串str1和str2,输出两个字符串的最长公共子串
//题目保证str1和str2的最长公共子串存在且唯一。
class LongestCommonSubstring {
public:

	string LCS(string text1, string text2) {
		// write code here
		int m = text1.length(), n = text2.length();
		vector<vector<int>> dp(m + 1, vector<int>(n + 1));
		int maxlen = INT_MIN, end;
		for (int i = 1; i <= m; i++) {
			char c1 = text1[i - 1];
			for (int j = 1; j <= n; j++) {
				char c2 = text2.at(j - 1);
				if (c1 == c2) {
					dp[i][j] = dp[i - 1][j - 1] + 1;
				}
				else {
					dp[i][j] = 0;
				}
				if (maxlen < dp[i][j]) {
					end = i;
					maxlen = dp[i][j];
				}
			}
		}
		string res = text1.substr(end - maxlen, maxlen);
		return res;


	}
};

inline int Fibonacci(int n) {
	vector<int>dp(n+1, 0);
	dp[0] = 0;dp[1] = 1;
	for (int i = 2;i <= n;++i) {
		dp[i] = dp[i - 1] + dp[i - 2];
	}
	return dp[n];
}

class GetLongestPalindrome {
public:
	int getLongestPalindrome(string A, int n) {
		// write code here
		vector<vector<int>>dp(n, vector<int>(n, 0));
		for (int i = 0;i < n;++i) {
			dp[i][i] = 1;
		}
		int maxlen = INT_MIN;
		for (int len = 2;len <= n;++len) {
			for (int start = 0;start <= n - len;++start) {
				int end = start + len - 1;
				if (len == 2 && A[end] == A[start]) {
					dp[start][end] = len;
					maxlen = len;
					continue;
				}
				if (A[start] == A[end] && dp[start + 1][end - 1]) {
					dp[start][end] = len;
					maxlen = len;
				}
			}
		}
		return maxlen;
	}
};
//120.三角形最小路径和
//给定一个三角形 triangle ，找出自顶向下的最小路径和。
//
//每一步只能移动到下一行中相邻的结点上。相邻的结点 在这里指的是 下标 与 上一层结点下标 相同或者等于 上一层结点下标 + 1 的两个结点
//。也就是说，如果正位于当前行的下标 i ，那么下一步可以移动到下一行的下标 i 或 i + 1 。

class MinimumTotal {
public:
	int minimumTotal(vector<vector<int>>& triangle) {
		int rows = triangle.size(), cols = triangle[rows - 1].size();
		vector<int>dp = triangle[rows - 1];
		for (int i = rows - 2;i >= 0;--i) {
			for (int j = 0;j < triangle[i].size();++j) {
				dp[j] = min(dp[j], dp[j + 1]) + triangle[i][j];
			}
		}
		return dp[0];
	}
};
//322. Coin Change
//You are given an integer array coins representing coins of different denominations and an integer amount representing a total amount of money.
//
//Return the fewest number of coins that you need to make up that amount.If that amount of money cannot be made up by any combination of the coins, return -1.
//
//You may assume that you have an infinite number of each kind of coin.
class CoinChange {
public:
	
	int coinChange(vector<int>& coins, int amount) {
		int n = coins.size();

		vector<int>dp(amount + 1,amount+1);
		dp[0] = 0;
		for (int i = 1;i <= amount;++i)
		{
			for (int j = 0;j < n;++j) {
				if (i >= coins[j])
					dp[i] = min(dp[i - coins[j]] + 1, dp[i]);
			}


		}
		if (dp[amount] == amount + 1)return -1;
		return dp[amount];
	}
};

//518. Coin Change 2
//You are given coins of different denominations and a total amount of money.
//Write a function to compute the number of combinations that make up that amount.
//You may assume that you have infinite number of each kind of coin.
class Change {
public:
	int change(int amount, vector<int>& coins) {
		int len = coins.size();
		//dp[i][j]:the number of combinations that make up that amount j using first ith denominations
		vector<vector<int>>dp(len + 1, vector<int>(amount + 1));
		dp[0][0] = 1;
		for (int i = 1;i <= len;++i)
		{
			dp[i][0] = 1;
			for (int j = 1;j <= amount;++j) {
				//either don't use the ith denomination at all or at least use one coin of ith denomination
				dp[i][j] = dp[i - 1][j] + (j >= coins[i - 1] ? dp[i][j - coins[i - 1]] : 0);
			}
		}
		return dp[len][amount];
	}

};
//198. House Robber
//不能抢相邻的房子，求最大收获
class Rob {
public:
	int rob(vector<int>& nums) {
		int len = nums.size();
		if (len == 1)return nums[0];
		if (len == 2)return max(nums[0], nums[1]);

		int pre = nums[0];
		int cur = max(nums[0], nums[1]);
		int next = 0;
		for (int i = 2;i < len;++i) {
			next = max(cur, pre + nums[i]);
			pre = cur;
			cur = next;
		}
		return next;
	}
};
//213. House Robber II
//第一个和最后一个房子是相邻的，不能同时抢
class Rob2 {
public:
	int rob(vector<int>& nums) {
		int len = nums.size();
		if (len == 1)return nums[0];
		//所有的情况可分为以下3种情况，
		//（1）第一个房子抢，最后一个房子不抢
		//（2）第一个房子不抢，最后一个房子也不抢
		//（3）第一个房子不抢，最够一个房子抢
		// helper(nums, 0, len - 2)其实是第1种情况和第2种情况之间的较大值，
		// helper(nums, 1, len - 1)则是第2种情况和第3种情况之间的较大值。
		// 再对他俩取较大值，得到的就是上述三种情况的最大值，即所有情况下的最大值。
		return max(helper(nums, 0, len - 2), helper(nums, 1, len - 1));
	}

	int helper(vector<int>& nums, int left, int right) {
		if (right == left)return nums[left];
		if (right == left + 1)return max(nums[left], nums[left + 1]);
		int pre = nums[left], cur = max(nums[left], nums[left + 1]), next = 0;
		for (int i = left + 2;i <= right;++i) {
			next = max(pre + nums[i], cur);
			pre = cur;
			cur = next;
		}
		return next;
	}
};


//NowCoder每天要给很多人发邮件。有一天他发现发错了邮件，把发给A的邮件发给了B，把发给B的邮件发给了A。于是他就思考，要给n个人发邮件，
//在每个人仅收到1封邮件的情况下，有多少种情况是所有人都收到了错误的邮件？
//即没有人收到属于自己的邮件
class MixEnvelope {
	/*当n个编号元素放在n个编号位置，元素编号与位置编号各不对应的方法数用D(n)表示，那么D(n - 1)就表示n - 1个编号元素放在n - 1个编号位置，各不对应的方法数，其它类推.
	第一步，把第n个元素放在一个位置，比如位置k，一共有n - 1种方法；
	第二步，放编号为k的元素，这时有两种情况：⑴把它放到位置n，那么，对于剩下的n - 1个元素，由于第k个元素放到了位置n，剩下n - 2个元素就有D(n - 2)种方法；⑵第k个元素不把它放到位置n，这时，对于这n - 1个元素，有D(n - 1)种方法；
	综上得到
	D(n) = (n - 1)[D(n - 2) + D(n - 1)]
	特殊地，D(1) = 0, D(2) = 1.*/
	long long mixEnvelope(int n) {
		if (n == 1)return 0;
		if (n == 2)return 1;
		long long  pre = 0, cur = 1, next = 0;
		for (int i = 3;i <= n;++i) {
			next = (i - 1)*(pre + cur);
			pre = cur;
			cur = next;
		}
		return next;
	}
};
//假设农场种中成熟的母牛每年都会生 1 头小母牛，并且永远都不会死。第一年有 1 只小母牛，从第二年开始，母牛开始生小母牛。每只小母牛 3 年后成熟又可以生小母牛。
//给定整数 N，求N年后牛的数量。
class CowNums {
	int cowNums(int n) {
		if (n < 4)return n;
		vector<int>dp(n+1);
		dp[0] = 0;dp[1] = 1;dp[2] = 2;dp[3] = 3;
		for (int i=4;i<=n;++i)
		{
			dp[i] = dp[i - 1] + dp[i - 3];
		}
		return dp[n];
	}
};

//64. Minimum Path Sum
//Given a m x n grid filled with non - negative numbers, find a path from top left to bottom right, which minimizes the sum of all numbers along its path.
//
//Note: You can only move either down or right at any point in time.
class MinPathSum {
public:
	int minPathSum(vector<vector<int>>& grid) {
		int rows = grid.size(), cols = grid[0].size();
		vector<vector<int>>dp(rows, vector<int>(cols));
		dp[0][0] = grid[0][0];
		for (int i = 1;i < rows;++i) {
			dp[i][0] = dp[i - 1][0] + grid[i][0];
		}
		for (int i = 1;i < cols;++i) {
			dp[0][i] = dp[0][i - 1] + grid[0][i];
		}
		for (int i = 1;i < rows;++i) {
			for (int j = 1;j < cols;++j) {
				dp[i][j] = min(dp[i - 1][j], dp[i][j - 1]) + grid[i][j];
			}
		}
		return dp[rows - 1][cols - 1];
	}
};

//62. Unique Paths
//A robot is located at the top - left corner of a m x n grid(marked 'Start' in the diagram below).
//
//The robot can only move either down or right at any point in time.The robot is trying to reach the bottom - right corner of the grid(marked 'Finish' in the diagram below).
//
//How many possible unique paths are there ?
class UniquePaths {
public:
	int uniquePaths(int m, int n) {
		vector<vector<int>>dp(m, vector<int>(n));
		dp[0][0] = 1;
		for (int i = 0;i < m;++i)dp[i][0] = 1;
		for (int i = 0;i < n;++i)dp[0][i] = 1;
		for (int i = 1;i < m;++i) {
			for (int j = 1;j < n;++j) {
				dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
			}
		}
		return dp[m - 1][n - 1];
	}
};