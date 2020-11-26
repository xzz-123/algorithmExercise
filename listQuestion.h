#pragma once
#include <vector>
using namespace std;

struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(nullptr) {}
};
//Write a program to find the node at which the intersection of two singly linked lists begins.
ListNode *getIntersectionNode(ListNode *headA, ListNode *headB);
ListNode* reverseListRecursively(ListNode* head);
ListNode* reverseListIteratively(ListNode* head);
ListNode* mergeTwoListsIteratively(ListNode* l1, ListNode* l2);
ListNode* mergeTwoListsRecursively(ListNode* l1, ListNode* l2);
ListNode* deleteDuplicatesRecursively(ListNode* head);
ListNode* deleteDuplicatesIteratively(ListNode* head);
ListNode* removeNthFromEnd(ListNode* head, int n);
ListNode* swapPairs(ListNode* head);
ListNode* addTwoNumbersReverseList(ListNode* l1, ListNode* l2);
ListNode* addTwoNumbersUseStack(ListNode* l1, ListNode* l2);
bool isPalindrome(ListNode* head);
vector<ListNode*> splitListToParts(ListNode* root, int k);
ListNode* oddEvenList(ListNode* head);