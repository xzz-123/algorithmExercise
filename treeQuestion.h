#pragma once
#include <algorithm>
#include <queue>
#include <unordered_map>
#include <stack>
#include <unordered_set>
#include <map>
#include <sstream>
#include "listQuestion.h"
using namespace std;
struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode() : val(0), left(nullptr), right(nullptr) {}
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
	TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
	
};


int maxDepth(TreeNode* root);
int maxDepthIteratively(TreeNode* root);
//给定一个二叉树，它的每个结点都存放着一个整数值。
//
//找出路径和等于给定数值的路径总数。
//
//路径不需要从根节点开始，也不需要在叶子节点结束，但是路径方向必须是向下的（只能从父节点到子节点）。
//
//二叉树不超过1000个节点，且节点数值范围是[-1000000, 1000000] 的整数。

class doubleRecursion {
public:
	int count = 0;
	int pathSum(TreeNode* root, int sum) {
		if (!root)return 0;
		dfs(root, sum);
		pathSum(root->left, sum);
		pathSum(root->right, sum);
		return count;
	}

	void dfs(TreeNode*root, int sum){
		if (!root)return;
		if (sum - root->val == 0)count++;
		dfs(root->left, sum - root->val);
		dfs(root->right, sum - root->val);
	}
};
class prefixSum {
public:

	unordered_map<int, int>count;
	int  pathSum(TreeNode*root, int sum){
		if (!root)return 0;
		count[0] = 1;
		return helper(root, sum, 0);
	}
	int helper(TreeNode* root, int sum, int pre){
		if (root == nullptr)return 0;
		pre += root->val;
		int res = 0;
		res += count[pre - sum];
		count[pre]++;
		res += helper(root->left, sum, pre) + helper(root->right, sum, pre);
		count[pre]--;
		return res;
	}
};
//给定两个非空二叉树 s 和 t，检验 s 中是否包含和 t 具有相同结构和节点值的子树。s 的一个子树包括 s 的一个节点和这个节点的所有子孙。s 也可以看做它自身的一棵子树

class SubtreeProblem {
public:
	bool isSubtree(TreeNode* s, TreeNode* t) {
		if (s == nullptr)return false;
		if (dfs(s, t))return true;
		return isSubtree(s->left, t) || isSubtree(s->right, t);
	}
	bool dfs(TreeNode*s, TreeNode*t){
		if (s == nullptr)return t == nullptr ? true : false;
		if (t == nullptr)return s == nullptr ? true : false;
		if (s->val != t->val)return false;
		return dfs(s->left, t->left) && dfs(s->right, t->right);
	}
};

//给定一个二叉树，找出其最小深度。

//最小深度是从根节点到最近叶子节点的最短路径上的节点数量。
int BfsMinDepth(TreeNode* root);
int DfsMinDepth(TreeNode* root);

//统计左叶子节点的和
int IterSumOfLeftLeaves(TreeNode* root);
int RecurSumOfLeftLeaves(TreeNode* root, bool isLeft = false);

//Given the root of a binary tree, return the length of the longest path, where each node in the path has the same value.
//This path may or may not pass through the root.
//
//The length of the path between two nodes is represented by the number of edges between them.

int longestUnivaluePath(TreeNode* root);
int bfs(TreeNode* root, int & count);//返回以root为根节点，不包括root的最长相同路径

//The thief has found himself a new place for his thievery again.There is only one entrance to this area, called the "root." Besides the root, 
//each house has one and only one parent house.After a tour, the smart thief realized that "all houses in this place forms a binary tree".It will 
//automatically contact the police if two directly - linked houses were broken into on the same night.
//Determine the maximum amount of money the thief can rob tonight without alerting the police.
int rob(TreeNode* root);//DP
int helper(TreeNode* root, unordered_map<TreeNode*, int>&m);
//maintain the information 
int rob1(TreeNode* root);
vector<int> helper1(TreeNode* root);
//Given a non - empty special binary tree consisting of nodes with the non - negative value, where each node in this tree has exactly two or zero sub - node.
//If the node has two sub - nodes, then this node's value is the smaller value among its two sub-nodes. More formally, the property 
//root.val = min(root.left.val, root.right.val) always holds.
//Given such a binary tree, you need to output the second minimum value in the set made of all the nodes' value in the whole tree.
//If no such second minimum value exists, output - 1 instead.
int findSecondMinimumValue(TreeNode* root);
//Given a non - empty binary tree, return the average value of the nodes on each level in the form of an array.
vector<double> averageOfLevels(TreeNode* root);
//Given a binary tree, find the leftmost value in the last row of the tree.
int findBottomLeftValueBfs(TreeNode* root);
int findBottomLeftValue(TreeNode* root);
void dfs(TreeNode* root, int height, pair<int, int>&res);
//Binary Tree Preorder Traversal
vector<int> preorderTraversal_iteratively(TreeNode* root);
void preorderTraversal_recursively(TreeNode* root,vector<int>&res);
//Binary Tree Inorder Traversal
void inorderTraversal_recursively(TreeNode* root, vector<int>&res);
vector<int> inorderTraversal_iteratively(TreeNode* root);
//Binary Tree Postorder Traversal
vector<int> postorderTraversal_iteratively(TreeNode* root);
void postorderTraversal(TreeNode* root, vector<int>&res);
//Given the root of a binary search tree and the lowest and highest boundaries as low and high, trim the tree so that all its elements lies in[low, high].
//Trimming the tree should not change the relative structure of the elements that will remain in the tree(i.e., any node's descendant should remain a descendant
//). It can be proven that there is a unique answer.
//
//Return the root of the trimmed binary search tree.Note that the root may change depending on the given bounds.
TreeNode* trimBST(TreeNode* root, int low, int high);
//Given a binary search tree, write a function kthSmallest to find the kth smallest element in it.
int kthSmallest(TreeNode* root, int k);
//Given the root of a Binary Search Tree(BST), convert it to a Greater Tree such that every key of the original BST is changed to the original key plus sum of 
//all keys greater than the original key in BST.
TreeNode* convertBST(TreeNode* root);
void rightFirstInorderTraversal(TreeNode*root, int &sum);
//Given a binary search tree(BST), find the lowest common ancestor(LCA) of two given nodes in the BST.
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q);
//Given an array where elements are sorted in ascending order, convert it to a height balanced BST.
//For this problem, a height - balanced binary tree is defined as a binary tree in which the depth of the two subtrees of every node never differ by more than 1.
using iter = vector<int>::const_iterator;
TreeNode* sortedArrayToBST(vector<int>& nums);
TreeNode* buildBST(iter b, iter e);
//Given the head of a singly linked list where elements are sorted in ascending order, convert it to a height balanced BST.
TreeNode* sortedListToBST(ListNode* head);
TreeNode* sortedListToBST(ListNode* head, ListNode* tail);
//Given the root of a Binary Search Tree and a target number k, return true if there exist two elements in the BST such that their sum is 
//equal to the given target.
bool findTarget(TreeNode* root, int k);
bool findTarget(TreeNode* root, int k, unordered_set<int>&s);
//Given a binary search tree with non-negative values, find the minimum absolute difference between values of any two nodes.

int getMinimumDifference(TreeNode* root);
//Given a binary search tree (BST) with duplicates, find all the mode(s) (the most frequently occurred element) in the given BST.


void update(int x);

void dfs(TreeNode* o);

vector<int> findMode(TreeNode* root);
//MorrisInorderTraversal
vector<int> Morris_inorderTraversal(TreeNode* root);
//Implement a trie with insert, search, and startsWith methods.
//Trie (we pronounce "try") or prefix tree is a tree data structure, which is used for retrieval of a key in a dataset of strings
//the Solution https://leetcode.com/problems/implement-trie-prefix-tree/solution/
class Trie {
public:
	/** Initialize your data structure here. */
	Trie() {}

	/** Inserts a word into the trie. */
	void insert(string word);

	/** Returns if the word is in the trie. */
	bool search(string word);

	/** Returns if there is any word in the trie that starts with the given prefix. */
	bool startsWith(string prefix);

private:
	bool isEnd = false;
	Trie* next[26] = {};
};
//Implement the MapSum class :
//
//MapSum() Initializes the MapSum object.
//void insert(String key, int val) Inserts the key - val pair into the map.If the key already existed, the original key - value pair will be overridden to the new one.
//int sum(string prefix) Returns the sum of all the pairs' value whose key starts with the prefix.
class MapSum {
public:
	/** Initialize your data structure here. */
	MapSum() {

	}

	void insert(string key, int val);

	int sum(string prefix);
private:
	map<string, int>mp;
};
//297. Serialize and Deserialize Binary Tree
class Codec {
public:

	// Encodes a tree to a single string.
	string serialize(TreeNode* root) {
		ostringstream out;
		serialize(root, out);
		return out.str();
	}

	// Decodes your encoded data to tree.
	TreeNode* deserialize(string data) {
		istringstream in(data);
		return deserialize(in);
	}

private:
	void serialize(TreeNode* root, ostringstream& out) {
		if (root) {
			out << root->val << ' ';
			serialize(root->left, out);
			serialize(root->right, out);
		}
		else {
			out << "# ";
		}
	}

	TreeNode* deserialize(istringstream& in) {
		string val;
		in >> val;
		if (val != "#") {
			TreeNode* root = new TreeNode(stoi(val));
			root->left = deserialize(in);
			root->right = deserialize(in);
			return root;
		}
		else return nullptr;
	}
};
