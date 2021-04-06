#pragma once
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