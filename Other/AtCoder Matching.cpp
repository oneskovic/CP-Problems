#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;
const ll mod = 1e9 + 7;
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n; cin >> n;
	vector<vector<bool>> conn_mat(n, vector<bool>(n));
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			bool a;
			cin >> a; conn_mat[i][j] = a;
		}
	}
	vector<vector<ll>> dp(n,vector<ll>((1 << n) + 1));

	// zeros[i] are all numbers that have i zeros in them
	vector<vector<ll>> zeros(n+1);
	int all_ones = (1 << n) - 1;
	for (int subset = 0; subset <= all_ones; subset++)
	{
		int zero_cnt = 0;
		int mask = 1;
		for (int i = 0; i < n; i++)
		{
			bool is_one = (mask & subset);
			if (!is_one)
			{
				zero_cnt++;
			}
			mask <<= 1;
		}
		zeros[zero_cnt].push_back(subset);
	}

	for (int i = 0, mask = 1; i < n; i++, mask <<= 1)
	{
		if (conn_mat[0][i])
			dp[0][mask^all_ones] = 1;
	}

	for (int i = 1; i < n; i++)
	{
		for (int subset : zeros[i+1])
		{
			for (int j = 0, mask = 1; j < n; j++, mask <<= 1)
			{
				bool is_one = (subset & mask);
				if (conn_mat[i][j] && !is_one)
				{
					dp[i][subset] += dp[i - 1][subset | mask];
					dp[i][subset] %= mod;
				}
			}
		}
	}
	ll solution = 0;
	for (int subset = 0; subset <= all_ones; subset++)
	{
		solution += dp.back()[subset];
		solution %= mod;
	}
	cout << solution << "\n";
	return 0;
}