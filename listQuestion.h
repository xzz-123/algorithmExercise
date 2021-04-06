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
bool hasCycle(ListNode *head);


//将给出的链表中的节点每k 个一组翻转，返回翻转后的链表
//如果链表中的节点数不是k 的倍数，将最后剩下的节点保持原样
//你不能更改节点中的值，只能更改节点本身。
ListNode* reverseKGroup(ListNode* head, int k);

//对于一个给定的链表，返回环的入口节点，如果没有环，返回null
ListNode *detectCycle(ListNode *head);

