#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int test_cnt; cin >> test_cnt;
	while (test_cnt--)
	{
		int n; cin >> n;
		vector<int> weights(n);
		for (int i = 0; i < n; i++)
			cin >> weights[i];

		vector<int> prefix_sum(n);
		prefix_sum[0] = weights[0];
		for (int i = 1; i < n; i++)
			prefix_sum[i] = prefix_sum[i - 1] + weights[i];
		
		ll solution = 0;
		ll suffix_sum = weights.back();
		int cnt_candies = 1;
		for (int i = n-2; i >= 0; i--)
		{
			auto lb = lower_bound(prefix_sum.begin(), prefix_sum.end(), suffix_sum);
			int j = lb - prefix_sum.begin();

			if (*lb == suffix_sum && j <= i)
			{
				solution = cnt_candies + j + 1;
			}
			suffix_sum += weights[i];
			cnt_candies++;
		}
		cout << solution << "\n";
	}

	return 0;
}
