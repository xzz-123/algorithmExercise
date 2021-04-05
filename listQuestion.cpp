#pragma once
#include <stack>
#include "listQuestion.h"
using namespace std;
//Write a program to find the node at which the intersection of two singly linked lists begins.
ListNode*getIntersectionNode(ListNode *headA, ListNode *headB) {
	ListNode*p1 = headA, *p2 = headB;

	while (p1 != p2){
		p1 = p1 ? p1->next : headB;
		p2 = p2 ? p2->next : headA;
	}
	return p1;
}
//Reverse a singly linked list.
ListNode* reverseListRecursively(ListNode* head) {
	if (head == nullptr || head->next == nullptr)return head;
	ListNode* p = reverseListRecursively(head->next);
	head->next->next = head;
	head->next = nullptr;
	return p;
}
ListNode* reverseListIteratively(ListNode* head) {
	if (head == nullptr || head->next == nullptr)return head;
	ListNode*prev = head;
	ListNode*n = head->next, *x;
	prev->next = nullptr;
	while (n){
		x = n->next;
		n->next = prev;
		prev = n;
		n = x;
	}
	return prev;
}
//Merge two sorted linked lists and return it as a new sorted list.The new list should be made by splicing together the nodes of the first two lists.
ListNode* mergeTwoListsIteratively(ListNode* l1, ListNode* l2) {

	ListNode*tail = new ListNode(-1);
	ListNode*preHead = tail;

	while (l1&&l2){
		if (l1->val < l2->val){
			tail->next = l1;
			l1 = l1->next;
		}
		else{
			tail->next = l2;
			l2 = l2->next;
		}
		tail = tail->next;
	}

	tail->next = l1 ? l1 : l2;

	return preHead->next;
}

ListNode* mergeTwoListsRecursively(ListNode* l1, ListNode* l2) {
	if (l1 == nullptr)return l2;
	if (l2 == nullptr)return l1;
	if (l1->val < l2->val){
		l1->next = mergeTwoListsRecursively(l1->next, l2);
		return l1;
	}
	else{
		l2->next = mergeTwoListsRecursively(l1, l2->next);
		return l2;
	}
}

ListNode* deleteDuplicatesRecursively(ListNode* head) {
	if (head == nullptr || head->next == nullptr){
		return head;
	}
	head->next = deleteDuplicatesRecursively(head->next);
	return head->val == head->next->val ? head->next : head;
}
ListNode* deleteDuplicatesIteratively(ListNode* head) {
	if (head == nullptr || head->next == nullptr)
		return head;
	ListNode* ret = head;
	while (head->next){
		if (head->next->val == head->val)
			head->next = head->next->next;
		else head = head->next;
	}
	return ret;
}
//Given the head of a linked list, remove the nth node from the end of the list and return its head.
ListNode* removeNthFromEnd(ListNode* head, int n) {

	ListNode *fast = head;
	while (n-- != 0){
		fast = fast->next;
	}
	if (fast == nullptr)return head->next;
	ListNode*slow = head;
	while (fast->next != nullptr){
		fast = fast->next;
		slow = slow->next;
	}
	slow->next = slow->next->next;
	return head;
}
//Given a linked list, swap every two adjacent nodes and return its head.
//You may not modify the values in the list's nodes. Only nodes itself may be changed.
ListNode* swapPairs(ListNode* head) {
	ListNode* dummy = new ListNode(-1);
	dummy->next = head;
	ListNode *pre = dummy;
	while (head&&head->next){
		ListNode*nn = head->next->next;
		pre->next = head->next;
		head->next->next = head;
		head->next = nn;
		pre = head;
		head = nn;
	}
	return dummy->next;
}
//You are given two non-empty linked lists representing two non-negative integers. 
//The most significant digit comes first and each of their nodes contain a single digit. Add the two numbers and return it as a linked list.
//You may assume the two numbers do not contain any leading zero, except the number 0 itself.
ListNode* addTwoNumbersReverseList(ListNode* l1, ListNode* l2) {
	l1 = reverseListIteratively(l1);
	l2 = reverseListIteratively(l2);
	ListNode* head = new ListNode(-1);
	ListNode* ret = head;
	bool carry = false;
	while (l1 || l2|| carry){
		int a = l1 ? l1->val : 0;
		int b = l2 ? l2->val : 0;

		head->val = (a + b + carry) % 10;

		carry = (a + b + carry) / 10;

		ListNode* next = new ListNode(-1);
		head->next = next;
		head = next;
		l1 = l1 ? l1->next : l1;
		l2 = l2 ? l2->next : l2;
	}

	ret = reverseListIteratively(ret);
	return ret->next;
}
ListNode* addTwoNumbersUseStack(ListNode* l1, ListNode* l2) {
	std::stack<int>s1, s2, res;
	while (l1){ s1.push(l1->val); l1 = l1->next; }
	while (l2){ s2.push(l2->val); l2 = l2->next; }
	int carry = 0;
	while (!s1.empty() || !s2.empty() || carry){
		int a = s1.empty() ? 0 : s1.top();
		int b = s2.empty() ? 0 : s2.top();
		if (!s1.empty())s1.pop();
		if (!s2.empty())s2.pop();

		int sum = (a + b + carry) % 10;
		carry = (a + b + carry) / 10;
		res.push(sum);
	}
	ListNode*head = new ListNode(-1);
	ListNode*ret = head;
	while (!res.empty()){

		head->val = res.top();
		res.pop();
		if (!res.empty()) {
			ListNode*next = new ListNode(-1);
			head->next = next;
			head = next;
		}
	}

	return ret;
}

//reverse the back half list,compare with the origin list
bool isPalindrome(ListNode* head) {
	if (head == nullptr || head->next == nullptr)return true;
	ListNode *fast = head, *slow = head, *pre = nullptr;
	while (fast&&fast->next){
		fast = fast->next->next;
		slow = slow->next;
	}
	while (slow){
		ListNode*next = slow->next;
		slow->next = pre;
		pre = slow;
		slow = next;
	}
	while (head&&pre){
		if (head->val != pre->val)return false;
		head = head->next;
		pre = pre->next;
	}
	return true;
}
//Given a (singly) linked list with head node root, write a function to split the linked list into k consecutive linked list "parts".

//The length of each part should be as equal as possible : no two parts should have a size differing by more than 1. This may lead to some parts being null.

//The parts should be in order of occurrence in the input list, and parts occurring earlier should always have a size greater than or equal parts occurring later.

//Return a List of ListNode's representing the linked list parts that are formed.

//Examples 1->2->3->4, k = 5 // 5 equal parts [ [1], [2], [3], [4], null ]
vector<ListNode*> splitListToParts(ListNode* root, int k) {
	ListNode*l1 = root;
	//the length of list
	int n = 0;
	while (l1){
		++n;
		l1 = l1->next;
	}
	vector<ListNode*>res(k, nullptr);
	int nOfPart = n / k;

	ListNode* next = nullptr;
	for (int i = 0; i < k; ++i){
		ListNode *left = root;
		//the first n%k parts have one more node than others
		for (int j = 0; j < nOfPart + (i < n%k ? 0 : -1); ++j){
			root = root->next;
		}
		//save the head of next part
		next = root ? root->next : nullptr;
		//disconnect
		if (root)root->next = nullptr;
		//move to next part
		root = next;
		res[i] = left;
	}
	return res;
}
//Given a singly linked list, group all odd nodes together followed by the even nodes.Please note here we are talking about the node number and not the value in the nodes.

//You should try to do it in place.The program should run in O(1) space complexity and O(nodes) time complexity.
ListNode* oddEvenList(ListNode* head) {
	if (head == nullptr)return head;
	ListNode *odd = head, *even = head->next, *eHead = even;
	while (even&&even->next){
		odd->next = even->next;
		odd = odd->next;
		even->next = odd->next;
		even = even->next;
	}
	odd->next = eHead;
	return head;
}

bool hasCycle(ListNode *head)
{
	if (head == nullptr)return false;
	ListNode* pSlow = head, *pFast = head;
	while (pFast&&pFast->next) {

		pSlow = pSlow->next;
		pFast = pFast->next->next;
		if (pSlow == pFast)return true;
	}
	return false;
}
