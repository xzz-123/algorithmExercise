#include <vector>
#include <algorithm>
#include <iostream>
#include "listQuestion.h"
#include "treeQuestion.h"
using namespace std;
class Solution {
public:
	int lengthOfLIS(vector<int>& nums) {
		int n = nums.size();
		if (n < 2)return n;
		vector<int>dp(n, 0);
		for (int i = 0; i < n; ++i){
			dp[i] = 1;
			for (int j = 0; j < i; ++j){
				if (nums[i] > nums[j])
					dp[i] = max(dp[i], dp[j] + 1);
			}
		}
		return *max_element(dp.begin(), dp.end());
	}
};

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
	int main(){
		TreeNode* root = new TreeNode(1);
		
		vector<int>a = { 1, 0 };
		vector<int>b = productExceptSelf(a);
		int d = minMoves2(a);
		string s = addStrings("0", "0");
		string con = convertToTitle(28);
		string c = convertToBase7(-7);

		int gc = gcd(9, 3);
		int count = countPrimes(10);
		int r = minDistance2("horse", "ros");

	}