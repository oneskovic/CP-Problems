#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int k, l; cin >> k >> l;
	int test_cnt; cin >> test_cnt;
	vector<int> queries; queries.reserve(test_cnt);
	while (test_cnt--)
	{
		int n; cin >> n;
		queries.push_back(n);
	}

	int n = *max_element(queries.begin(), queries.end());
	vector<vector<bool>> dp(n + 1, vector<bool>(2));
	dp[0][0] = 1;
	dp[0][1] = 0;
	vector<int> steps = { 1,k,l };
	for (int i = 1; i <= n; i++)
	{
		for (bool j : {0, 1})
		{
			dp[i][j] = !j;
			for (int step : steps)
			{
				if (i - step >= 0 && dp[i - step][!j] == j)
				{
					dp[i][j] = j;
				}
			}
		}
	}
	for (int i = 0; i <= n; i++)
	{
		cout << dp[i][0] << " ";
	}
	cout << "\n";
	for (int i = 0; i <= n; i++)
	{
		cout << dp[i][1] << " ";
	}
	for (int i: queries)
	{
		cout << (!dp[i][0] ? 'A' : 'B');
	}
	return 0;
}