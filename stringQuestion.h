#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

/*p为模式串，下标从0开始*/
void GetNext(string P, int next[]);
/*在S中找到P第一次出线的位置*/
int KMP(string S, string P, int next[]);
//Given two strings s and t, write a function to determine if t is an anagram of s.
bool isAnagram(string s, string t);
//Given a string s which consists of lowercase or uppercase letters, return the length of the longest palindrome that can be built with those letters
//Letters are case sensitive, for example, "Aa" is not considered a palindrome here.
int longestPalindrome(string s);
//Given a string, determine if it is a palindrome, considering only alphanumeric characters and ignoring cases.
bool isPalindrome(string s);
//Given two strings s and t, determine if they are isomorphic.
//
//Two strings are isomorphic if the characters in s can be replaced to get t.
//
//All occurrences of a character must be replaced with another character while preserving the order of characters.No two characters may map to the same character but a character may map to itself.
bool isIsomorphic(string s, string t);

//Given a string, your task is to count how many palindromic substrings in this string.

//The substrings with different start indexes or end indexes are counted as different substrings even they consist of same characters.
int countSubstrings(string s);
//Determine whether an integer is a palindrome.An integer is a palindrome when it reads the same backward as forward.

//Follow up : Could you solve it without converting the integer to a string ?
bool isPalindrome(int x);
//Give a string s, count the number of non - empty(contiguous) substrings that have the same number of 0's and 1's, and all the 0's and all the 1's in these substrings are grouped consecutively.

//Substrings that occur multiple times are counted the number of times they occur.
//Explanation
//First, I count the number of 1 or 0 grouped consecutively.
//For example "0110001111" will be[1, 2, 3, 4].
//
//Second, for any possible substrings with 1 and 0 grouped consecutively, the number of valid substring will be the minimum number of 0 and 1.
//For example "0001111", will be min(3, 4) = 3, ("01", "0011", "000111")
int countBinarySubstrings(string s);

class AddBigNumber {
public:
	/**
	 * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
	 * 计算两个数之和
	 * @param s string字符串 表示第一个整数
	 * @param t string字符串 表示第二个整数
	 * @return string字符串
	 */
	string solve(string s, string t);
};