#pragma once
#include <vector>
#include<algorithm>
#include <unordered_map>
#include <numeric>
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

class NumberOfArithmeticSlices {
public:
	int numberOfArithmeticSlices(vector<int>& nums) {
		int len = nums.size();
		if (len == 1)return 0;
		vector<int>dp(len + 1);
		dp[1] = 0;dp[2] = 0;
		int pre = nums[1] - nums[0], cur, curlen = 0;
		//pre记录i-1 th和 i-2th 的差，cur记录ith和i-1 th的差
		//curlen记录以i-1 th结尾的arithmetic的个数
		for (int i = 3;i <= len;++i) {
			cur = nums[i - 1] - nums[i - 2];
			if (pre == cur)++curlen;
			else {
				pre = cur;
				curlen = 0;
			}
			//前i个元素组成的序列中airthmeic的个数==
			//(1)第i个元素不和第i-1，i-2个元素等差，那么dp[i]=dp[i-1]
			//(2)第i个元素和第i-1，i-2个元素等差，那么以i-1 th结尾的
			//arithmetic们加上第i个元素，就又各自成了一个新的arithmetic，故
			//dp[i]=dp[i-1]+curlen.
			dp[i] = pre == cur ? dp[i - 1] + curlen : dp[i - 1];
		}
		return dp[len];
	}
};
//343.整数拆分
//给定一个正整数 n，将其拆分为至少两个正整数的和，并使这些整数的乘积最大化。 返回你可以获得的最大乘积
class IntergerBreak {
public:
	int integerBreak(int n) {
		if (n == 2)return 1;

		vector<int>dp(n + 1);
		dp[2] = 1;
		for (int i = 3;i <= n;++i) {
			for (int j = 2;j <= i - 1;++j) {
				dp[i] = max(dp[i], max(j*dp[i - j], j*(i - j)));
			}
		}
		return dp[n];
	}
};
//279. Perfect Squares
//Given an integer n, return the least number of perfect square numbers that sum to n.
//
//A perfect square is an integer that is the square of an integer; in other words, it is the product of some integer with itself.
//For example, 1, 4, 9, and 16 are perfect squares while 3 and 11 are not.
class NumSquares {
public:
	int numSquares(int n) {
		vector<int>dp(n + 1, n);
		dp[0] = 0;
		for (int i = 1;i <= n;++i) {
			for (int j = 1;j*j <= i;++j) {
				dp[i] = min(dp[i - j * j] + 1, dp[i]);
			}
		}
		return dp[n];
	}
};
//91.解码方法
//一条包含字母 A - Z 的消息通过以下映射进行了 编码 ：
//
//'A' -> 1
//'B' -> 2
//...
//'Z' -> 26
//要 解码 已编码的消息，所有数字必须基于上述映射的方法，反向映射回字母（可能有多种方法）。例如，"111" 可以将 "1" 中的每个 "1" 映射为 "A" ，从而得到 "AAA" ，或者可以将 "11" 和 "1"（分别为 "K" 和 "A" ）映射为 "KA" 。注意，"06" 不能映射为 "F" ，因为 "6" 和 "06" 不同。
//
//给你一个只含数字的 非空 字符串 num ，请计算并返回 解码 方法的 总数 。
//
//题目数据保证答案肯定是一个 32 位 的整数。
class NumberCodings {
public:
	int numDecodings(string s) {
		if (s[0] == '0')return 0;
		int n = s.size();
		vector<int> dp(n + 1);
		dp[0] = 1;
		dp[1] = 1;
		for (int i = 2;i <= n;++i) {
			//0前面必须是1或者2，不然就无解
			if (s[i-1]=='0')
			{
				if (s[i - 2] =='1'||s[i-2]=='2')dp[i] = dp[i-2];
				else return 0;
			}
			//ith可以和i-1th构成一个数，也可以算做两个数
			else if(s[i - 2]=='1'||s[i-2]=='2'&&s[i-1]>='1'&&s[i-1]<='6')
			{
				dp[i] = dp[i - 1] + dp[i-2];
			}
			//ith无法和i-1th 构成一个数，只能算作两个数
			else dp[i] = dp[i - 1];
		}
		return dp[n];
	}
};
//300. Longest Increasing Subsequence(Medium)
//给你一个整数数组 nums ，找到其中最长严格递增子序列的长度。
//
//子序列是由数组派生而来的序列，删除（或不删除）数组中的元素而不改变其余元素的顺序。例如，[3, 6, 2, 7] 是数组[0, 3, 1, 6, 2, 2, 7] 的子序列。

class LengthOfLIS {
public:
	int lengthOfLIS(vector<int>& nums) {
		int n = nums.size();
		if (n == 1)return 1;
		//dp[i]:nums[0]~nums[i]以nums[i]结尾的最长递增子序列长度
		vector<int>dp(n, 1);
		dp[0] = 1;
		int ret = 0;

		for (int i = 1;i < n;++i) {
			for (int j = i - 1;j >= 0;--j)
			{
				if (nums[i] > nums[j])
				{
					dp[i] = max(dp[i], dp[j] + 1);
				}
			}
			ret = max(ret, dp[i]);
		}
		return ret;
	}

};
//646. 最长数对链
//给出 n 个数对。 在每一个数对中，第一个数字总是比第二个数字小。
//
//现在，我们定义一种跟随关系，当且仅当 b < c 时，数对(c, d) 才可以跟在(a, b) 后面。我们用这种形式来构造一个数对链。
//
//	给定一个数对集合，找出能够形成的最长数对链的长度。你不需要用到所有的数对，你可以以任何顺序选择其中的一些数对来构造
//本质就是最长上升子序列
class FindLongestChain {
public:
	static bool com(vector<int>a, vector<int>b) {
		return a[0]<b[0];
	}
	int findLongestChain(vector<vector<int>>& pairs) {
		int n = pairs.size();
		vector<int>dp(n,1);
		sort(pairs.begin(), pairs.end(), com);
		dp[0] = 1;
		int ret = 0;
		for (int i = 1;i < n;++i) {
			for (int j = i - 1;j >= 0;--j) {
				if (pairs[i][0] > pairs[j][1])
					dp[i] = max(dp[i], dp[j] + 1);
			}
			ret = max(ret, dp[i]);
		}
		return ret;
	}
};
//用贪心算法
class FindLongestChain2 {
public:
	static bool cmp(vector<int>a, vector<int>b) {
		return a[1] < b[1];
	}
	int findLongestChain(vector<vector<int>>& pairs) {
		int n = pairs.size();
		sort(pairs.begin(), pairs.end(), cmp);
		int pre = pairs[0][1];
		int count = 1;
		for (int i = 1;i < n;++i) {
			if (pairs[i][0] > pre)
			{
				++count;
				pre = pairs[i][1];
			}
		}
		return count;
	}
};
//376. Wiggle Subsequence
//Medium
//
//A wiggle sequence is a sequence where the differences between successive numbers strictly alternate between positive and negative.The first difference(if one exists) may be either positive or negative.A sequence with two or fewer elements is trivially a wiggle sequence.
//
//For example, [1, 7, 4, 9, 2, 5] is a wiggle sequence because the differences(6, -3, 5, -7, 3) alternate between positive and negative.
//In contrast, [1, 4, 7, 2, 5] and [1, 7, 4, 5, 5] are not wiggle sequences.The first is not because its first two differences are positive, and the second is not because its last difference is zero.
//A subsequence is obtained by deleting some elements(possibly zero) from the original sequence, leaving the remaining elements in their original order.
//
//Given an integer array nums, return the length of the longest wiggle subsequence of nums.
class WiggleMaxLength {
public:
	int wiggleMaxLength(vector<int>& nums) {
		int n = nums.size();
		//up表示当前到位置为止最大的上升子序列的长度，down则相反
		//初始时都为1
		int up = 1, down = 1;
		for (int i = 1;i < n;++i) {
			//此时能接在前面的最大下降子序列的后面
			if (nums[i] > nums[i - 1]) {
				up = down + 1;
			}//此时能接在前面的最大上升子序列的后面
			else if (nums[i] < nums[i - 1]) {
				down = up + 1;
			}
		}
		return max(up, down);
	}
};
//416. 分割等和子集
//给定一个只包含正整数的非空数组。是否可以将这个数组分割成两个子集，使得两个子集的元素和相等。
class CanPartition {
public:
	//转化为01背包问题
	bool canPartition(vector<int>& nums) {
		int sum = accumulate(nums.begin(), nums.end(), 0);
		int maxNum = *max_element(nums.begin(), nums.end());
		int n = nums.size();
		if (n < 2)return false;

		if (sum &1)return false;
		sum /= 2;
		if (maxNum>sum)
		{
			return false;
		}
		//dp[i][j]：从nums[0]到nums[i]中任选数字，加起来可以等于j就为true，否则为false
		vector<vector<int>>dp(n, vector<int>(sum + 1, false));
		for (int i = 0;i < n;++i)dp[i][0] = true;
		dp[0][nums[0]] = true;
		for (int i = 1;i < n;++i) {
			for (int j = 1;j <= sum;++j) {
				if (nums[i] > j)dp[i][j] = dp[i - 1][j];
				else dp[i][j] = max(dp[i - 1][j - nums[i]], dp[i - 1][j]);
			}
		}
		return dp[n - 1][sum];
	}


};