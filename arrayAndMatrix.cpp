#include "arrayAndMatrix.h"
void moveZeroes(vector<int>& nums)
{
	int position = 0;

	int n = nums.size();

	int j = 0;

	for (int i = 0; i < n;++i) {
		if (nums[i] != 0) {
			nums[position] = nums[i];
			++position;
		}
	}
	for (;position < n;++position) {
		nums[position] = 0;
	}
}

std::vector<std::vector<int>> matrixReshape(vector<vector<int>>& nums, int r, int c)
{
	int row = nums.size();
	if (row == 0)return nums;
	int oc = nums[0].size();
	if (oc == 0)return nums;

	if (r*c != row * oc) {
		return nums;
	}
	vector<vector<int>>ret(r);

	int count = 0;
	for (auto i : nums) {
		i.reserve(c);
		for (int j : i) {
			ret[count / c].push_back(j);
			++count;
		}
	}
	return ret;
}

int findMaxConsecutiveOnes(vector<int>& nums)
{
	int max = 0, cur = 0;
	for (int i = 0;i < nums.size();i++)
	{
		if (nums[i] & 1)
		{
			max = max > ++cur ? max : cur;
		}
		else cur = 0;
	}
	return max;
}

bool searchMatrix(vector<vector<int>>& matrix, int target)
{
	int r = matrix.size();
	int c = matrix[0].size();
	int cr = 0, cc = c - 1;
	while (cr < r&&cc >= 0) {
		if (matrix[cr][cc] == target)return true;
		else if (matrix[cr][cc] < target) {
			++cr;
		}
		else --cc;
	}
	return false;
}

bool check(vector<vector<int>>&matrix, int mid, int k)
{
	int n = matrix.size();
	int i = n - 1, j = 0, num = 0;
	while (i >= 0 && j < n) {
		if (matrix[i][j] <= mid) {
			num += i + 1;
			++j;
		}
		else --i;
	}
	return num >= k;
}

int kthSmallest(vector<vector<int>>& matrix, int k)
{
	int n = matrix.size();
	int l = matrix[0][0], r = matrix[n - 1][n - 1];
	while (l < r) {
		int mid = l + ((r - l) >> 1);
		if (check(matrix, mid, k)) {
			r = mid;
		}
		else l = mid + 1;
	}
	return l;
}

int findDuplicate(vector<int>& nums)
{
	int n = nums.size();
	if (n == 2)return nums[0];
	int slow = nums[0];
	int fast = nums[nums[0]];
	while (slow != fast) {
		slow = nums[slow];
		fast = nums[nums[fast]];
	}
	slow = 0;
	while (slow != fast) {
		slow = nums[slow];
		fast = nums[fast];
	}
	return fast;
}

int findShortestSubArray(vector<int>& nums)
{
	unordered_map<int, int>first, count;
	int degree = 0, res = 0;
	for (int i = 0;i < nums.size();++i) {
		if (first.count(nums[i]) == 0)first[nums[i]] = i;
		if (++count[nums[i]] > degree) {
			degree = count[nums[i]];
			res = i - first[nums[i]] + 1;
		}
		else if (count[nums[i]] == degree)
			res = min(res, i - first[nums[i]] + 1);
	}
	return res;
}

bool isToeplitzMatrix(vector<vector<int>>& matrix)
{
	int r = matrix.size();
	int c = matrix[0].size();
	for (int i = 1;i < r;++i) {
		for (int j = 1;j < c;++j) {
			if (matrix[i][j] != matrix[i - 1][j - 1])return false;
		}
	}
	return true;
}

int arrayNesting(vector<int>& a)
{
	size_t maxsize = 0;
	for (int i = 0; i < a.size(); i++) {
		size_t size = 0;
		for (int k = i; a[k] >= 0; size++) {
			int ak = a[k];
			a[k] = -1; // mark a[k] as visited;
			k = ak;
		}
		maxsize = max(maxsize, size);
	}

	return maxsize;
}

int maxChunksToSorted(vector<int>& arr)
{
	int res = 1;
	int max_c = arr[0];
	for (int i = 1;i < arr.size();++i) {
		if (i > max_c)++res;
		max_c = max(max_c, arr[i]);
	}
	return res;
}

bool isBipartite(vector<vector<int>>& graph)
{
	int n = graph.size();
	vector<int>colors(n, 0);
	for (int i = 0;i < n;++i) {
		if (colors[i] == 0 && !validColor(graph, colors, 1, i))
			return false;
	}
	return true;
}

bool validColor(vector<vector<int>>&graph, vector<int>&colors, int color, int node)
{
	if (colors[node] != 0) {
		return colors[node] == color;
	}
	colors[node] = color;
	for (int adjacent : graph[node]) {
		if (!validColor(graph, colors, -color, adjacent))return false;
	}
	return true;
}

std::vector<int> spiralOrder(vector<vector<int> > &matrix)
{
	
	int rows = matrix.size(), cols = matrix[0].size();
	int total = rows * cols;
	vector<int>res;
	int top = 0, bot = rows - 1, left = 0, right = cols - 1;
	while (total>=1) {
		for (int i = left; 1<= total&&i <= right;++i) {
			res.push_back(matrix[top][i]);
			--total;
		}
		++top;
		for (int i = top;1 <= total&&i <= bot;++i) {
			res.push_back(matrix[i][right]);--total;
		}
		--right;
		for (int i = right;1 <= total&&i >= left;--i) {
			res.push_back(matrix[bot][i]);--total;
		}
		--bot;
		for (int i = bot;1 <= total&&i >= top;--i) {
			res.push_back(matrix[i][left]);--total;
		}
		++left;
		
	}
	return res;
}

std::vector<std::vector<int> > threeSum(vector<int> &num)
{
	vector<vector<int>> res;
	sort(num.begin(), num.end());
	int len = num.size();
	for (int i = 0;i < len - 2;++i) {
		if (i == 0 || num[i] != num[i - 1]) {
			int left = i + 1, right = len - 1;
			if (num[i] > 0)break;
			while (left < right) {
				while (left < right&&num[i] + num[left] + num[right] > 0)right--;
				if (left < right&&num[i] + num[left] + num[right] == 0) {
					vector<int>vec = { num[i],num[left],num[right] };
					res.push_back(vec);
					int curleft = num[left];
					while (curleft == num[left])++left;
				}
				else {
					++left;
				}
			}

		}

	}
	return res;
}

