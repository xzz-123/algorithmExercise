#include <vector>
#include <algorithm>
#include <iostream>
#include "listQuestion.h"
#include "treeQuestion.h"
#include "arrayAndMatrix.h"
#include "backTracking.h"
#include "binarySerach.h"
#include "divideAndConquer.h"
#include "serach.h"
#include "Sort.h"
#include "stringQuestion.h"
#include "dynamicPlannging.h"
#include "greedy.h"
#include "graph.h"
using namespace std;



//最多交易两次
	int maxProfit2(vector<int>& prices) {
		int n = prices.size();
		int dp0 = 0, dp1 = -prices[0], dp2 = 0, dp3 = -prices[0], dp4 = 0;
		for (int i = 1; i < n; ++i){
			dp1 = max(dp0 - prices[i], dp1);
			dp2 = max(dp1 + prices[i], dp2);
			dp3 = max(dp2 - prices[i], dp3);
			dp4 = max(dp3 + prices[i], dp4);
		}
		return max(max(max(dp0, dp1), max(dp2, dp3)), dp4);
	}
	int greedy(vector<int>&prices){
		int max = 0;
		for (int i=1; i < prices.size(); ++i){
			if (prices[i] > prices[i - 1])
				max += prices[i] - prices[i - 1];
		}
		return max;
	}
	//最多交易K次
	int maxProfitk(int k, vector<int>& prices) {
		if (k < 1)return 0;
		if (k >= (int)prices.size() / 2)return greedy(prices);
		vector<vector<int>>dp(k, vector<int>(2, 0));
		for (int i = 0; i < k; ++i)
			dp[i][0] = INT_MIN;
		for (int p : prices){
			dp[0][0] = max(dp[0][0], -p);
			dp[0][1] = max(dp[0][0] + p, dp[0][1]);
			for (int i = 1; i < k; ++i){
				dp[i][0] = max(dp[i - 1][1] - p, dp[i][0]);
				dp[i][1] = max(dp[i][0] + p, dp[i][1]);
			}
		}
		return dp[k - 1][1];
	}
	/*Given two words word1 and word2, find the minimum number of steps required to make word1 and word2 the same, 
	where in each step you can delete one character in either string.

		Example 1:
		Input : "sea", "eat"
		Output : 2
		Explanation : You need one step to make "sea" to "ea" and another step to make "eat" to "ea".*/
	int minDistance(string word1, string word2) {
		vector<vector<int>>dp(word1.size()+1, vector<int>(word2.size()+1, 0));
		if (word1.size()==word2.size()&&word2.size()==1)
		{
			return word2[0] == word1[0] ? 0 : 2;
		}
		for (int i = 0; i <= word1.size(); ++i){
			for (int j = 0; j <= word2.size(); ++j){
				if (i == 0 || j == 0)
					dp[i][j] = i + j;
				else if (word1[i-1] == word2[j-1])
					dp[i][j] = dp[i - 1][j - 1];
				else
					dp[i][j] = 1 + min(dp[i - 1][j], dp[i][j - 1]);
			}
		}
		return dp[word1.size()][word2.size()];
	}
	/*Given two words word1 and word2, find the minimum number of operations required to convert word1 to word2.

		You have the following 3 operations permitted on a word :

	Insert a character
	Delete a character
	Replace a character*/
	int minDistance2(string word1, string word2) {
		int m = word1.size(), n = word2.size();
		if (m == 0 || n == 0)return m + n;
		vector<vector<int>>dp(m + 1, vector<int>(n + 1, 0));
		for (int i = 0; i <= m; ++i){
			for (int j = 0; j <= n; ++j){
				if (i == 0 || j == 0)dp[i][j] = i + j;
				else if (word1[i - 1] == word2[j - 1])
					dp[i][j] = dp[i - 1][j - 1];
				else dp[i][j] = min(min(dp[i - 1][j], dp[i][j - 1]), dp[i - 1][j - 1]) + 1;
			}
		}
		return dp[m][n];
	}
	/*Count the number of prime numbers less than a non - negative number, n.

	Example:

	Input : 10
	Output : 4
	Explanation : There are 4 prime numbers less than 10, they are 2, 3, 5, 7.*/
	int countPrimes(int n) {
		vector<bool>notPrimes(n + 1, false);
		int count = 0;
		for (int i = 2; i < n; ++i){
			if (notPrimes[i])continue;
			++count;
			for (int j = i; (long long)i*j < n; ++j){
				notPrimes[i*j] = true;
			}
		}
		return count;
	}
	bool isEven(const int a){
		return a % 2 == 0 ? true : false;
	}
	//最大公约数
	int gcd(const int a, const int b){
		if (a < b)return gcd(b, a);
		if (b == 0)return a;
		bool isAEven = isEven(a), isBEven = isEven(b);
		if (isAEven&&isBEven)return gcd(a >>1, b >>1);
		else if (isAEven&&!isBEven)return gcd(a >>1, b);
		else if (!isAEven&&isBEven)return gcd(a, b >> 1);
		else return gcd(b, a-b);
	}
	//最小公倍数
	int lcm(const int a, const int b){
		return a*b / gcd(a, b);
	}
	string convertToBase7(int num) {

		if (num < 0)return "-"+convertToBase7(-1 * num);
		string res;
		while (num > 0){
			res += num % 7;
			num /= 7;
		}
		return string(res.rbegin(), res.rend());
	}

	string convertToTitle(int n) {
		string alphabet("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
		string res("");
		while (n > 0){
			res += alphabet[(n-1) % 26 ];
			n /= 26;
		}
		reverse(res.begin(), res.end());
		return res;
	}
	/*Given two non - negative integers num1 and num2 represented as string, return the sum of num1 and num2.

	Note:

	The length of both num1 and num2 is < 5100.
	Both num1 and num2 contains only digits 0 - 9.
	Both num1 and num2 does not contain any leading zero.
	You must not use any built - in BigInteger library or convert the inputs to integer directly.*/
	string addStrings(string num1, string num2) {
		int n = max(num1.size(), num2.size());
		string r("");
		reverse(num1.begin(), num1.end());
		reverse(num2.begin(), num2.end());
		int carry = 0;
		for (int i = 0; i < n; ++i){
			carry += (i < num1.size() ? num1[i]-'0' : 0);
			carry += (i < num2.size() ? num2[i] -'0': 0);
			r.push_back(carry % 10 + '0');
			carry /= 10;
		}
		if (carry) r.push_back(carry + '0');
		reverse(r.begin(), r.end());
		return r;
	}
	/*Given a non - empty integer array, find the minimum number of moves required to make all array elements equal,
	where a move is incrementing a selected element by 1 or decrementing a selected element by 1.*/
	int partition(vector<int>&nums, int l, int r){
		int x = rand() % (r - l + 1) + l;
		swap(nums[x], nums[r]);
		int pivot = nums[r];
		int i = l - 1;
		for (int j = l; j < r; ++j){
			if (nums[j] <= pivot)
				swap(nums[++i], nums[j]);
		}
		swap(nums[i + 1], nums[r]);
		return i+1;
	}
	int findKthSmallest(vector<int>&nums, int l, int r, int k){
		int res = partition(nums, l, r);
		if (res == k)return nums[res];
		else if (res < k)return findKthSmallest(nums, res + 1, r, k);
		return findKthSmallest(nums, l, res - 1, k);
	}
	int minMoves2(vector<int>& nums) {
		if (nums.size() <= 1)return 0;
		int kth = findKthSmallest(nums, 0, nums.size() - 1, nums.size() / 2);
		int r = 0;
		for (int num : nums){
			r += abs(num - kth);
		}
		return r;
	}

	vector<int> productExceptSelf(vector<int>& nums) {
		int common = 1, zero = 1;
		vector<int>ret(nums.size());
		int i = 0;
		while (i != nums.size() && nums[i] != 0){
			common *= nums[i];
			++i;
		}
		if (i != nums.size()){
			for (int num : ret)num = 0;
			for (int j = 0; j < nums.size(); ++j)
				if (j != i)zero *= nums[j];
			ret[i] = zero;
			return ret;
		}
		common /= nums[0];
		ret[0] = common;
		for (int i = 1; i < nums.size(); ++i){
			ret[i] = ret[i - 1] * nums[i - 1] / nums[i];
		}
		return ret;
	}
	
	int main() {
		Exist exi;

		auto a = exi.exist(vector<vector<char>>{{'a'}},"a");
//		RestoreIpAddresses ria;
//		ria.restoreIpAddresses("1111");
//		PacificAtlantic pa;
//		pa.pacificAtlantic(vector<vector<int>>{{1, 2, 2, 3, 5}, {3, 2, 3, 4, 4}, {2, 4, 5, 3, 1}, {6, 7, 1, 4, 5}, {5, 1, 1, 2, 4}});
//		ShortestPathBinaryMatrix spb;
//		spb.shortestPathBinaryMatrix(vector<vector<int>>{ {0, 1}, { 1, 0 }});
//		FindCommonNumbers fcn;
//		vector<vector<int>>tvec{ {1, 4, 15, 7,6}, { 1,4,15,6 }, { 1,6,7 },{1,2,4,15,6} };
//		auto vec=fcn.findCommonNumbers(tvec);
//		auto vec01 = fcn.findCommonNumbers1(tvec);
//		LengthOfLongestSubstring lls;
//		lls.lengthOfLongestSubstring("abcabcbb");
//		LongestValidParentheses1 lvp1;
//		lvp1.longestValidParentheses1("(()");
//		LongestValidParentheses lvp;
//		lvp.longestValidParentheses(")()())");
//		LongestPalindrome lp;
//		lp.longestPalindrome(string("aacabdkacaa"));
//		FindRedundantDirectedConnection frd;
//		frd.findRedundantDirectedConnection(vector<vector<int>>{ {1, 2}, { 1, 3 }, { 2, 3 }});
//		FindCircleNum fc;
//		fc.findCircleNum(vector<vector<int>>{ {1, 1, 0},{1, 1, 0},{0, 0, 1} });
//		CalcEquation ce;
//		CalcEquation1 ce1;
//		CalcEquation2 ce2;
//		ce2.calcEquation(vector<vector<string>>{{"x1", "x2"}, {"x2", "x3"}, {"x3", "x4"}, {"x4", "x5"}},
//			vector<double>{3.0, 4.0, 5.0, 6.0},
//			vector<vector<string>>{{"x1", "x5"}, {"x5", "x2"}, {"x2", "x4"}, {"x2", "x2"}, {"x2", "x9"}, {"x9", "x9"}});
//		Surrounded sd;
//		vector<vector<char>>ac
//		{ {'X', 'O', 'X', 'X'}, {'O', 'X', 'O', 'X'}, {'X', 'O', 'X', 'O'},
//{'O', 'X', 'O', 'X'}, {'X', 'O', 'X', 'O'}, {'O', 'X', 'O', 'X'} };
//		sd.solve(ac);
//		LongestConsecutive lc;
//		lc.longestConsecutive(vector<int>{100, 4, 200, 1, 3, 2});
//		ReconstructQueue rec;
//		vector<vector<int>>vec1= {{40, 11}, {81, 12}, {32, 60}, {36, 39}, {76, 19}, {11, 37}, {67, 13}, {45, 39}, {99, 0}, {35, 20}, {15, 3}, {62, 13}, {90, 2}, {86, 0}, {26, 13}, {68, 32}, {91, 4}, {23, 24}, {73, 14}, {86, 13}, {62, 6}, {36, 13}, {67, 9}, {39, 57}, {15, 45}, {37, 26}, {12, 88}, {30, 18}, {39, 60}, {77, 2}, {24, 38}, {72, 7}, {96, 1}, {29, 47}, {92, 1}, {67, 28}, {54, 44}, {46, 35}, {3, 85}, {27, 9}, {82, 14}, {29, 17}, {80, 11}, {84, 10}, {5, 59}, {82, 6}, {62, 25}, {64, 29}, {88, 8}, {11, 20}, {83, 0}, {94, 4}, {43, 42}, {73, 9}, {57, 32}, {76, 24}, {14, 67}, {86, 2}, {13, 47}, {93, 1}, {95, 2}, {87, 8}, {8, 78}, {58, 16}, {26, 75}, {26, 15}, 
//			{24, 56}, {69, 9}, {42, 22}, {70, 17}, {34, 48}, {26, 39}, {22, 28}, {21, 8}, {51, 44}, {35, 4}, {25, 48}, {78, 18}
//			, {29, 30}, {13, 63}, {68, 8}, {21, 38}, {56, 20}, {84, 14}, {56, 27}, {60, 40}, {98, 0}, {63, 7}, {27, 46}, {70, 
//			13}, {29, 23}, {49, 6}, {5, 64}, {67, 11}, {2, 31}, {59, 8}, {93, 0}, {50, 39}, {84, 6}, {19, 39}};
//		auto res11=rec.reconstructQueue(vec1);
//		vector<vector<int>>matrix = { {1,2,3,4},{5,6,7,8},{9,10,11,12} };
//		spiralOrder(matrix);
//
//		Shopping_offer sh;
//		sh.shoppingOffers(vector<int>{ 2, 5 }, vector<vector<int>>{ {3, 0, 5}, { 1, 2, 10 } }, vector<int>{ 3, 2 });
//		vector<vector<char>>board233 = {{'5', '3', '.', '.', '7', '.', '.', '.', '.'},
//			{'6', '.', '.', '1', '9', '5', '.', '.', '.'},
//			{'.', '9', '8', '.', '.', '.', '.', '6', '.'},
//			{'8', '.', '.', '.', '6', '.', '.', '.', '3'},
//			{'4', '.', '.', '8', '.', '3', '.', '.', '1'},
//			{'7', '.', '.', '.', '2', '.', '.', '.', '6'},
//			{'.', '6', '.', '.', '.', '.', '2', '8', '.'},
//			{'.', '.', '.', '4', '1', '9', '.', '.', '5'},
//			{'.', '.', '.', '.', '8', '.', '.', '7', '9'}};
//
//		SudokuSolver sud;
//		sud.solveSudoku(board233);
//		
//		SubsetsWithDup sw;
//		sw.subsetsWithDup(vector<int>{1, 2, 2});
//		Subsets sb;
//		sb.subsets(vector<int>{1, 2, 3});
//		FindTargetSumWays fts;
//		fts.findTargetSumWays(vector<int>{ 1, 1, 1, 1, 1 }, 3);
//		FindLongestChain fin;
//		fin.findLongestChain(vector<vector<int>>{ {-6, 9}, { 1, 6 }, { 8, 10 }, { -1, 4 }, { -6, -2 }, { -9, 8 }, { -5, 3 }, { 0, 3 }});
//		LengthOfLIS leng;
//		leng.lengthOfLIS(vector<int>{10, 9, 2, 5, 3, 7, 101, 18});
//		NumberCodings nbc;
//		nbc.numDecodings("1123");
//		NumSquares numsq;
//		numsq.numSquares(12);
//		NumberOfArithmeticSlices nu;
//		
//		nu.numberOfArithmeticSlices(vector<int>{1,2,3,8,9,10});
//		CoinChange co;
//		vector<int>coins{ 1,2,5 };
//		int resc=co.coinChange(coins,11);
//		MinimumTotal mi;
//		vector<vector<int>>triangle = { {2}, {3, 4}, {6, 5, 7}, {4, 1, 8, 3} };
//		mi.minimumTotal(triangle);
//		auto ts = threeSum(vector<int>{1, 2, -2, -1});
//		int fn = Fibonacci(1000);
//		
//		AddBigNumber ad;
//		string ress = ad.solve("11", "123");
//		TreeNode *TreeNode1 = new TreeNode(1);
//		TreeNode *TreeNode2 = new TreeNode(2);
//		TreeNode *TreeNode3 = new TreeNode(3);
//		TreeNode *TreeNode4 = new TreeNode(4);
//		TreeNode *TreeNode5 = new TreeNode(5);
//		TreeNode *TreeNode6 = new TreeNode(6);
//		TreeNode *TreeNode7 = new TreeNode(7);
//		TreeNode4->left = TreeNode2;
//		TreeNode4->right = TreeNode6;
//		TreeNode2->left = TreeNode1;
//		TreeNode2->right = TreeNode3;
//		TreeNode6->left = TreeNode5;
//		TreeNode6->right = TreeNode7;
//		
//		vector<int>res1 = postorder(TreeNode4);
//		vector<int>res2 = inorderTraversal_iteratively(TreeNode4);
//		vector<int>nums1 = { 5,2,3,1 };
//		SelectSort se;
//		se.sortArray(nums1);
//		BubbleSort b;
//		b.sortArray(nums1);
//		QuickSort q;
//		
//		//q.sortArray(nums1);
//		HeapSort h;
//		//h.heapSort(nums1);
//		MergeSort me;
//		me.mergerSort(nums1,0,nums1.size()-1);
//		RobotMoveCount r;
//		r.movingCount(1, 2, 1);
//		GenerateTrees g;
//		g.generateTrees(3);
//		diffToC d;
//		d.diffWaysToCompute("2-1-1");
//		SplitArray sp;
//		vector<int>nums = { 7, 2, 5, 10, 8 };
//			int m = 2;
//			sp.splitArray(nums, m);
//		ShortestD s;
//		vector<vector<int>>grid = { {1,0,2,0,1},{0,0,0,0,0},{0,0,1,0,0} };
//		int res=s.shortestDistance(grid);
//		pathInMatrix p;
//		vector<vector<char>>board = {vector<char>{'A', 'B', 'C', 'E'}, {'S', 'F', 'C', 'S'}, {'A', 'D', 'E', 'E'}};
//		string word = "ABCCED";
//		p.exist(board, word);
		
		/*SudokuSolver s;
		vector<vector<char>> board  ={ vector<char>{'5', '3', '.', '.', '7', '.', '.', '.', '.'},
			vector<char>{'6', '.', '.', '1', '9', '5', '.', '.', '.'},
			vector<char>{'.', '9', '8', '.', '.', '.', '.', '6', '.'},
			vector<char>{'8', '.', '.', '.', '6', '.', '.', '.', '3'},
			vector<char>{'4', '.', '.', '8', '.', '3', '.', '.', '1'},
			vector<char>{'7', '.', '.', '.', '2', '.', '.', '.', '6'},
			vector<char>{'.', '6', '.', '.', '.', '.', '2', '8', '.'},
			vector<char>{'.', '.', '.', '4', '1', '9', '.', '.', '5'},
			vector<char>{'.', '.', '.', '.', '8', '.', '.', '7', '9'}};
		s.solveSudoku(board);*/

	}