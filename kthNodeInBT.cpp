#include "treeQuestion.h"
//给定一棵二叉搜索树，请找出其中第k大的节点。
class Solution {
private:
	int res, k;
	void inOrder(TreeNode* root) {
		if (root == nullptr)return;
		inOrder(root->right);
		if (k == 0)return;
		if (--k == 0)res = root->val;
		inOrder(root->left);
	}
public:
	int kthLargest(TreeNode* root, int k) {
		this->k = k;
		inOrder(root);
		return res;
	}