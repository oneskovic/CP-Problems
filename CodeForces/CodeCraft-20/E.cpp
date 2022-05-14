#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n, p, k; cin >> n >> p >> k;
	vector<pair<ll,int>> value_as_audience(n);
	for (int i = 0; i < n; i++)
	{
		cin >> value_as_audience[i].first;
		value_as_audience[i].second = i;
	}
	sort(value_as_audience.begin(), value_as_audience.end(), greater<pair<ll,int>>());

	vector<vector<ll>> value_as_position(n, vector<ll>(p));
	for (int i = 0; i < n; i++)
		for (int j = 0; j < p; j++)
			cin >> value_as_position[i][j];
	
	vector<ll> dp((1 << p) + 1);
	int all_ones = (1 << p) - 1;
	for (int pos = p - 1, mask = 1; pos >= 0; pos--, mask <<= 1)
	{
		int unsorted_index = value_as_audience[0].second;
		dp[all_ones ^ mask] = value_as_position[unsorted_index][pos];
	}
	dp[all_ones] = value_as_audience[0].first;

	auto old_dp = dp;
	for (int i = 1; i < n; i++)
	{
		int unsorted_index = value_as_audience[i].second;
		for (int subset = 0; subset < (1<<p); subset++)
		{
			ll max_if_taken_for_pos = 0;
			ll max_less_zero = 0;
			int zeros_cnt = 0;
			for (int pos = p-1, mask = 1; pos >= 0; pos--, mask <<= 1)
			{
				bool is_available = (mask & subset);
				if (!is_available)
				{
					zeros_cnt++;
					ll new_val = old_dp[subset | mask] + value_as_position[unsorted_index][pos];
					max_if_taken_for_pos = max(max_if_taken_for_pos, new_val);
					max_less_zero = max(max_less_zero, old_dp[subset | mask]);
				}
			}
			if (zeros_cnt > i+1)
			{
				continue;
			}

			ll value_if_taken_for_audience = 0;
			int taken_audience = i - zeros_cnt;
			if (taken_audience + 1< k)
			{
				value_if_taken_for_audience = max_less_zero + value_as_audience[i].first;
			}
			if (taken_audience < k)
			{
				value_if_taken_for_audience = max(value_if_taken_for_audience, old_dp[subset] + value_as_audience[i].first);
			}
			dp[subset] = max(max(max_if_taken_for_pos, value_if_taken_for_audience),dp[subset]);
		}
		old_dp = dp;
	}
	cout << dp[0] << "\n";
	return 0;
}
