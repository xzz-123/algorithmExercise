
#include "stringQuestion.h"
void GetNext(string P, int next[])
{
	int p_len = P.size();
	int i = 0, j = -1;
	next[0] = -1;

	while (i<p_len)
	{
		if (j==-1||P[i]==P[j])
		{
			++i;
			++j;
			next[i] = j;
		}
		else
			j = next[j];
	}
}

int KMP(string S, string P, int next[])
{
	GetNext(P, next);

	int i = 0, j = 0;
	int s_len = S.size(), p_len = P.size();

	while (i<s_len&&j<p_len)
	{
		if (j==-1||S[i]==P[j])//P的第一个字符不匹配或S[i]==P[j]
		{
			++i; ++j;
		}
		else
		{
			j = next[j];//当前字符串匹配失败，进行跳转
		}
	}
	if (j==p_len)//匹配成功
	{
		return i - j;
	}
	return -1;
}

bool isAnagram(string s, string t)
{
	int size = s.size();
	if (size != t.size())return false;
	vector<int>count(26);
	for (int i = 0; i < size; ++i){
		count[s[i] - 'a']++;
		count[t[i] - 'a']--;
	}
	for (int i : count){
		if (i != 0)
			return false;
	}
	return true;
}

bool isPalindrome(string s)
{
	for (int i = 0, j = s.size() - 1; i < j; ++i, --j){
		while (!isalnum(s[i]) && i < j)++i;
		while (!isalnum(s[j]) && i < j)--j;
		if (toupper(s[i]) != toupper(s[j]))return false;
	}
	return true;
}

bool isPalindrome(int x)
{
	if (x < 0 || (x != 0 && x % 10 == 0))return false;
	int rev = 0;
	while (x > rev){
		rev = x % 10 + rev * 10;
		x /= 10;
	}
	return x == rev || x == rev / 10;
}

int countBinarySubstrings(string s)
{
	int cur = 1, pre = 0, res = 0;
	for (int i = 1; i < s.size(); ++i) {
		if (s[i] == s[i - 1])++cur;
		else {
			res += min(pre, cur);
			pre = cur;
			cur = 1;
		}
	}
	return res + min(pre, cur);
}

int longestPalindrome(string s)
{
	unordered_map<int, int>m;
	for (auto c : s){
		m[c - 'A']++;
	}
	int ret = 0;
	for (auto i : m){
		ret += i.second % 2;
	}
	return ret == 0 ? s.size() : s.size() - ret + 1;
}

bool isIsomorphic(string s, string t)
{
	int size = s.size();
	vector<int>v1(256, -1), v2(256, -1);
	for (int i = 0; i < size; ++i){
		if (v1[s[i]] != v2[t[i]])return false;
		v1[s[i]] = v2[t[i]] = i;
	}
	return true;
}

int countSubstrings(string s)
{
	int res = 0;
	int n = s.size();
	//以每一位为中心扩展
	for (int i = 0; i < n; ++i){
		for (int j = 0; i - j >= 0 && i + j < n&&s[i - j] == s[i + j]; ++j)++res;//奇数
		for (int j = 0; i - 1 - j >= 0 && i + j < n&&s[i - 1 - j] == s[i + j]; ++j)++res;//偶数
	}
	return res;
}

std::string AddBigNumber::solve(string s, string t)
{
	// write code here
	int len1 = s.size();
	int len2 = t.size();
	string res = "";
	int carry = 0;
	int i = len1 - 1, j = len2 - 1;
	int sum = 0;
	while (i >= 0 || j >= 0 || carry) {
		int x = i < 0 ? 0 : s[i--] - '0';
		int y = j < 0 ? 0 : t[j--] - '0';
		sum = x + y + carry;
		if (sum >= 10)carry = 1;
		else carry = 0;
		res = to_string(sum % 10) + res;
	}

	return res;
}
