#include <vector>
#include<algorithm>
using namespace std;
//������
//����һ������Ϊ n �����ӣ�������Ӽ����������ȵ� m �Σ�m��n����������n>1����m>1����ÿ�����ӵĳ��ȼ�Ϊ k[0],k[1]...k[m-1] ������ k[0]*k[1]*...*k[m-1] 
//���ܵ����˻��Ƕ��٣�
class CutRope {
public:
	int cuttingRope(int n) {
		vector<int>dp(n + 1);
		dp[2] = 1;
		for (int i = 3;i < n + 1;++i) {
			for (int j = 2;j < i;++j) {
				dp[i] = max(dp[i], max(j*(i - j), j*dp[i - j]));
			}
		}
		return dp[n];
	}
};
//��Ʊ���������
class MaxProfit {
public:
	int maxProfit(vector<int>& prices) {
		int minPrice = INT_MAX, ret = 0;
		for (auto &p : prices) {
			ret = max(ret, p - minPrice);
			minPrice = min(minPrice, p);
		}
		return ret;
	}
};