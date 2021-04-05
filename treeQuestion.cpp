#include "treeQuestion.h"

int maxDepth(TreeNode* root)
{
	if (root == nullptr)return 0;
	return max(maxDepth(root->left), maxDepth(root->right)) + 1;
}

int maxDepthIteratively(TreeNode* root)
{
	if (root == nullptr)return 0;
	queue<TreeNode*>q;
	q.push(root);
	int ret = 0;
	while (!q.empty()){
		int size = q.size();
		while (size){
			TreeNode* node = q.front();
			q.pop();
			if (node->left)q.push(node->left);
			if (node->right)q.push(node->right);
			--size;
		}
		++ret;
	}
	return ret;
}

int BfsMinDepth(TreeNode* root)
{
	{
		if (!root)return 0;
		queue<pair<TreeNode*, int>>que;
		que.emplace(root, 1);
		int depth = 0;
		while (!que.empty()){
			TreeNode*node = que.front().first;
			depth = que.front().second;
			que.pop();
			if (!node->left&&!node->right)
				return depth;
			if (node->left)que.emplace(node->left, depth + 1);
			if (node->right)que.emplace(node->right, depth + 1);
		}
		return depth;
	}
}

int DfsMinDepth(TreeNode* root)
{
	
		if (root == nullptr) 
			return 0;
		if (root->left == nullptr && root->right == nullptr) 
			return 1;
		int min_depth = INT_MAX;
		if (root->left != nullptr) {
			min_depth = min(DfsMinDepth(root->left), min_depth);
		}
		if (root->right != nullptr) {
			min_depth = min(DfsMinDepth(root->right), min_depth);
		}

		return min_depth + 1;
}

int IterSumOfLeftLeaves(TreeNode* root)
{
	if (root == nullptr)return 0;
	int ans = 0;
	stack<TreeNode*>s;
	s.push(root);
	while (!s.empty()){
		TreeNode *node = s.top();
		s.pop();
		if (node->left){
			if (node->left->left == nullptr&&node->left->right == nullptr)
				ans += node->left->val;
			else s.push(node->left);
		}
		if (node->right){
			if (node->right->left != nullptr || node->right->right != nullptr)
				s.push(node->right);
		}
	}
	return ans;
}

int RecurSumOfLeftLeaves(TreeNode* root, bool isLeft /*= false*/)
{
	if (root == nullptr)return 0;
	if (!root->left&&!root->right)return isLeft ? root->val : 0;
	return RecurSumOfLeftLeaves(root->left, true) + RecurSumOfLeftLeaves(root->right);
}


int longestUnivaluePath(TreeNode* root)
{
	int count = 0;
	bfs(root, count);
	return count;
}

int bfs(TreeNode* root, int & count) //返回以root为根节点，不包括root的最长相同路径
{
	if (root == nullptr)return 0;
	int l = bfs(root->left, count);
	int r = bfs(root->right, count);
	int lp = 0, rp = 0;
	if (root->left&&root->left->val == root->val)lp += l;//如果root跟左儿子能连起来，如果不能连起来lp就为0
	if (root->right&&root->right->val == root->val)rp += r;//如果root跟右儿子能连起来
	count = max(count, lp + rp);
	return max(lp, rp) + 1;
}

int rob(TreeNode* root)
{
	if (root == nullptr)return 0;
	unordered_map<TreeNode*, int>m;
	return helper(root, m);
}

int helper(TreeNode* root, unordered_map<TreeNode*, int>&m)
{
	if (root == nullptr)return 0;
	auto iter = m.find(root);
	if (iter != m.end())
		return iter->second;

	int rootUnrobbed = helper(root->left, m) + helper(root->right, m);
	int rootRobbed = 0;
	if (root->left)rootRobbed += helper(root->left->left, m) + helper(root->left->right, m);
	if (root->right)rootRobbed += helper(root->right->left, m) + helper(root->right->right, m);
	int ans = max(rootRobbed + root->val, rootUnrobbed);
	m.insert(make_pair(root, ans));
	return ans;
}

TreeNode* sortedListToBST(ListNode* head, ListNode* tail)
{
	if (head == tail)return nullptr;

	ListNode* p1 = head, *p2 = head;
	while (p2 != tail&&p2->next != tail){
		p1 = p1->next;
		p2 = p2->next->next;
	}

	TreeNode* root = new TreeNode(p1->val);
	root->left = sortedListToBST(head, p1);
	root->right = sortedListToBST(p1->next, tail);
	return root;
}

int rob1(TreeNode* root)
{
	if (root == nullptr)return 0;
	return max(helper1(root)[0], helper1(root)[1]);
}

vector<int> helper1(TreeNode* root)
{
	vector<int> maxMoney(2, 0);//1,max money if root robbed,2 max money if root unrobbed
	if (root == nullptr)return maxMoney;
	vector<int> l = helper1(root->left);
	vector<int> r = helper1(root->right);
	maxMoney[0] = root->val + l[1] + r[1];
	maxMoney[1] = max(l[0], l[1]) + max(r[0], r[1]);
	return maxMoney;
}

int findSecondMinimumValue(TreeNode* root)
{
	if (root == nullptr)return -1;
	if (root->left == nullptr&&root->right == nullptr)return -1;
	int minv = root->val;
	int left = root->left->val, right = root->right->val;
	if (root->left->val == minv)left = findSecondMinimumValue(root->left);
	if (root->right->val == minv)right = findSecondMinimumValue(root->right);
	if (left != -1 && right != -1)
		return min(left, right);
	if (left != -1)return left;
	return right;
}

vector<double> averageOfLevels(TreeNode* root)
{
	vector<double>ans;
	if (root == nullptr)return ans;
	queue<TreeNode*>q;
	q.push(root);
	while (!q.empty()){
		int s = q.size();
		double sum = 0;
		for (int i = 0; i < s; ++i){
			TreeNode* node = q.front();
			q.pop();
			if (node->left)q.push(node->left);
			if (node->right)q.push(node->right);
			sum += node->val;
		}
		ans.push_back(sum / s);
	}
	return ans;
}

int findBottomLeftValueBfs(TreeNode* root)
{
	queue<TreeNode*>q;
	q.push(root);
	while (!q.empty()){
		root = q.front();
		q.pop();
		if (root->right)q.push(root->right);
		if (root->left)q.push(root->left);
	}
	return root->val;
}

int findBottomLeftValue(TreeNode* root)
{
	pair<int, int>res(root->val, 1);
	dfs(root, 1, res);
	return res.first;
}

void dfs(TreeNode* root, int height, pair<int, int>&res)
{
	if (root->left == nullptr&&root->right == nullptr&&height > res.second)
		res = make_pair(root->val, height);
	if (root->left)dfs(root->left, height + 1, res);
	if (root->right)dfs(root->right, height + 1, res);
	return;
}

void dfs(TreeNode* o)
{
	if (!o) {
		return;
	}
	dfs(o->left);
	update(o->val);
	dfs(o->right);
}

vector<int> preorderTraversal_iteratively(TreeNode* root)
{
	vector<int>res;
	if (root == nullptr)return res;
	stack<TreeNode*>s;
	s.push(root);
	while (!s.empty()){
		TreeNode* node = s.top();
		s.pop();
		res.push_back(node->val);
		if (node->right)s.push(node->right);
		if (node->left)s.push(node->left);
	}
	return res;
}

void preorderTraversal_recursively(TreeNode* root, vector<int>&res)
{
	if (root == nullptr)return;
	res.push_back(root->val);
	preorderTraversal_recursively(root->left, res);
	preorderTraversal_recursively(root->right, res);
}

vector<int> inorderTraversal_iteratively(TreeNode* root)
{
	vector<int>res;
	if (root == nullptr)return res;
	stack<TreeNode*>s;
	s.push(root);
	while (!s.empty()){
		
		while (s.top()->left){
			s.push(s.top()->left);
		}
		while (!s.empty())
		{
			TreeNode* cur = s.top();
			s.pop();
			res.push_back(cur->val);
			if (cur->right)
			{
				s.push(cur->right);
				break;
			}
		}
		
	}
	return res;
}

void inorderTraversal_recursively(TreeNode* root, vector<int>&res)
{
	if (root == nullptr)return;
	inorderTraversal_recursively(root->left, res);
	res.push_back(root->val);
	inorderTraversal_recursively(root->right, res);
}

vector<int> postorderTraversal_iteratively(TreeNode* root)
{
	vector<int>res;
	if (root == nullptr)return res;
	stack<TreeNode*>s;
	TreeNode* pre = nullptr;
	s.push(root);
	while (!s.empty()){
		while (s.top()->left){
			s.push(s.top()->left);
		}
		
		while (!s.empty())
		{
			TreeNode*cur = s.top();
			if (cur->right == pre || cur->right == nullptr) {
				s.pop();
				res.push_back(cur->val);
				pre = cur;
			}
			else
			{
				s.push(cur->right);
				break;
			}
		}
		
	}
	return res;
}

void postorderTraversal(TreeNode* root, vector<int>&res)
{
	if (root == nullptr)return;
	postorderTraversal(root->left, res);

	postorderTraversal(root->right, res);
	res.push_back(root->val);
}

TreeNode* trimBST(TreeNode* root, int low, int high)
{
	if (root == nullptr)return root;
	if (root->val > high)
		return trimBST(root->left, low, high);

	if (root->val < low)
		return trimBST(root->right, low, high);

	root->left = trimBST(root->left, low, high);
	root->right = trimBST(root->right, low, high);

	return root;
}

int kthSmallest(TreeNode* root, int k)
{
	vector<int>path;
	stack<TreeNode*>s;
	s.push(root);
	while (root || !s.empty()){
		while (root){
			s.push(root);
			root = root->left;
		}
		TreeNode* node = s.top();
		s.pop();
		path.push_back(node->val);
		root = node->right;
	}
	return path[k - 1];
}

TreeNode* convertBST(TreeNode* root)
{
	int sum = 0;
	rightFirstInorderTraversal(root, sum);
	return root;
}

void rightFirstInorderTraversal(TreeNode*root, int &sum)
{
	if (root == nullptr)return;
	if(root->right)rightFirstInorderTraversal(root->right, sum);
	root->val += sum;
	sum = root->val;
	if(root->left)rightFirstInorderTraversal(root->left, sum);
	return;
}

TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q)
{
	while ((root->val - p->val)*(root->val - q->val) > 0)
		root = root->val - p->val > 0 ? root->left : root->right;
	return root;
}

TreeNode* sortedArrayToBST(vector<int>& nums)
{
	if (nums.empty())return nullptr;

	return buildBST(nums.begin(), nums.end());
}

TreeNode* buildBST(iter b, iter e)
{
	if (b >= e)return nullptr;

	iter m = b + (e - b) / 2;
	TreeNode *node = new TreeNode(*m);

	node->left = buildBST(b, m);
	node->right = buildBST(m + 1, e);

	return node;
}

TreeNode* sortedListToBST(ListNode* head)
{
	if (head == nullptr)return nullptr;
	return  sortedListToBST(head, nullptr);
}

bool findTarget(TreeNode* root, int k)
{
	unordered_set<int>s;
	return findTarget(root, k, s);
}

bool findTarget(TreeNode* root, int k, unordered_set<int>&s)
{
	if (root == nullptr)return false;
	if (s.find(k - root->val) != s.end())return true;
	s.insert(root->val);
	return findTarget(root->left, k, s) || findTarget(root->right, k, s);
}

int min1 = INT_MAX;
int pre = -1;
int getMinimumDifference(TreeNode* root)
{
	if (root == nullptr)return -1;
	getMinimumDifference(root->left);
	if (pre != -1)
		min1 = min(min1, root->val - pre);
	pre = root->val;
	getMinimumDifference(root->right);
	return min1;
}

vector<int> answer;
int base, count1 = 0, maxCount = 0;
void update(int x)
{
	if (x == base) {
		++count1;
	}
	else {
		count1 = 1;
		base = x;
	}
	if (count1 == maxCount) {
		answer.push_back(base);
	}
	if (count1 > maxCount) {

		answer = vector<int> {base};
		maxCount = count1;
	}
}
vector<int> findMode(TreeNode* root)
{
	dfs(root);
	return answer;
}

vector<int> Morris_inorderTraversal(TreeNode* root)
{
	vector<int>res;
	if (root == nullptr)return res;
	TreeNode* cur = root;
	while (cur){
		if (cur->left){
			TreeNode* node = cur->left;
			while (node->right&&node->right != cur)node = node->right;

			if (node->right == nullptr)
			{
				node->right = cur;
				cur = cur->left;
			}
			else
			{
				node->right = nullptr;
				res.push_back(cur->val);
				cur = cur->right;
			}
		}
		else{
			res.push_back(cur->val);
			cur = cur->right;
		}
	}
	return res;
}



std::vector<int> postorder(TreeNode* root)
{
	if (!root)return vector<int>();
	deque<int>res;
	stack<TreeNode*>stk;
	stk.push(root);

	while (!stk.empty()) {
		TreeNode* cur = stk.top();
		stk.pop();
		res.push_front(cur->val);
		if (cur->left)stk.push(cur->left);
		if (cur->right)stk.push(cur->right);
	}
	vector<int>vec(res.begin(), res.end());
	return vec;
}

void Trie::insert(string word)
{
	Trie* node = this;
	for (char ch : word){
		ch -= 'a';
		if (node->next[ch] == nullptr){
			node->next[ch] = new Trie();
		}
		node = node->next[ch];
	}
	node->isEnd = true;
}

bool Trie::search(string word)
{
	Trie* node = this;
	for (char ch : word){
		ch -= 'a';
		if (node->next[ch] == nullptr)return false;
		node = node->next[ch];
	}
	return node->isEnd;
}

bool Trie::startsWith(string prefix)
{
	Trie* node = this;
	for (char ch : prefix){
		ch -= 'a';
		if (node->next[ch] == nullptr)return false;
		node = node->next[ch];
	}
	return true;
}

void MapSum::insert(string key, int val)
{
	mp[key] = val;
}

int MapSum::sum(string prefix)
{
	int sum = 0, n = prefix.size();
	for (auto it = mp.lower_bound(prefix); it != mp.end() && it->first.substr(0, n) == prefix; ++it)
		sum += it->second;
	return sum;
}
