#pragma once
#include <stack>
#include <queue>
using namespace std;
//implement a first in first out(FIFO) queue using only two stacks.The implemented queue should support all the functions of a normal queue
//(push, peek, pop, and empty).
class MyQueue {
public:
	/** Initialize your data structure here. */
	MyQueue() {

	}

	/** Push element x to the back of queue. */
	void push(int x) {
		s1.push(x);
	}

	/** Removes the element from in front of queue and returns that element. */
	int pop() {

		int ret = peek();
		s2.pop();
		return ret;
	}

	/** Get the front element. */
	int peek() {
		if (s2.empty()){
			while (!s1.empty()){
				int i = s1.top();
				s1.pop();
				s2.push(i);
			}
		}

		return s2.top();
	}

	/** Returns whether the queue is empty. */
	bool empty() {
		return s1.empty() && s2.empty();
	}
	stack<int>s1, s2;
};
//implement a first in first out(FIFO) queue using  stack.
class MyStack {
public:
	/** Initialize your data structure here. */
	MyStack() {

	}

	/** Push element x onto stack. */
	void push(int x) {
		q.push(x);
		for (int i = 0; i < q.size() - 1; ++i){
			q.push(q.front());
			q.pop();
		}
	}

	/** Removes the element on top of the stack and returns that element. */
	void pop() {
		q.pop();
	}

	/** Get the top element. */
	int top() {
		return q.front();
	}

	/** Returns whether the stack is empty. */
	bool empty() {
		return q.empty();
	}
	queue<int>q;
};
//Design a stack that supports push, pop, top, and retrieving the minimum element in constant time
class MinStack {
public:
	/** initialize your data structure here. */
	MinStack() {

	}

	void push(int x) {
		if (s2.empty() || x <= getMin())
		{
			s2.push(x);
		}
		s1.push(x);

	}

	void pop() {
		if (top() == getMin())
		{
			s2.pop();
		}

		s1.pop();
	}

	int top() {
		return s1.top();
	}

	int getMin() {
		return s2.top();
	}
	stack<int>s1, s2;

};
//Given a string s containing just the characters '(', ')', '{', '}', '[' and ']', determine if the input string is valid.
//
//An input string is valid if:
//
//Open brackets must be closed by the same type of brackets.
//Open brackets must be closed in the correct order.
bool isValid(string s) {
	stack<int>st;
	for (char c : s){
		switch (c){
		case '(':st.push(')'); break;
		case '[':st.push(']'); break;
		case '{':st.push('}'); break;
		default:
			if (st.empty() || c != st.top())return false;
			else st.pop();
		}
	}
	return st.empty();
}
//Given a list of daily temperatures T, return a list such that, for each day in the input, tells you how many days you would have to wait until a warmer temperature.If there is no future day for which this is possible, put 0 instead.
//
//For example, given the list of temperatures T = [73, 74, 75, 71, 69, 72, 76, 73], your output should be[1, 1, 4, 2, 1, 1, 0, 0].
vector<int> dailyTemperatures(vector<int>& T) {
	int size = T.size();
	vector<int>res(size);
	for (int i = size - 1; i >= 0; --i){
		int j = i + 1;
		while (j < size&&T[i] >= T[j]){
			if (res[j]>0)j += res[j];
			else j = size;
		}
		if (j < size)res[i] = j - i;
	}
	return res;
}
//Given a circular array(the next element of the last element is the first element of the array), 
//print the Next Greater Number for every element.The Next Greater Number of a number x is the first greater number to its traversing - order next 
//in the array, which means you could search circularly to find its next greater number.If it doesn't exist, output -1 for this number.
vector<int> nextGreaterElements(vector<int>& nums) {
	int n = nums.size();
	vector<int> next(n, -1);
	stack<int> s; // index stack
	for (int i = 0; i<2 * n; ++i){
		int num = nums[i%n];
		while (!s.empty() && num>nums[s.top()]){
			next[s.top()] = num;
			s.pop();
		}
		if (i < n)s.push(i);
	}
	return next;
}