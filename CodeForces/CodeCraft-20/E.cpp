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
	sort(value_as_audience.begin(), value_as_audience.end());

	vector<vector<ll>> value_as_position(n, vector<ll>(p));
	for (int i = 0; i < n; i++)
		for (int j = 0; j < p; j++)
			cin >> value_as_position[i][j];
	
	vector<ll> dp((1 << p) + 1);
	auto old_dp = dp;
	for (int i = 0; i < n; i++)
	{
		int unsorted_index = value_as_audience[i].second;
		for (int subset = 0; subset < (1<<p); subset++)
		{
			ll max_if_taken_for_pos = 0;
			int zeros_cnt = 0;
			for (int pos = 0, mask = 1; pos < p; pos++, mask <<= 1)
			{
				bool is_available = (mask & subset);
				if (!is_available)
				{
					zeros_cnt++;
					ll new_val = old_dp[subset | mask] + value_as_position[unsorted_index][pos];
					max_if_taken_for_pos = max(max_if_taken_for_pos, new_val);
				}
			}
			int taken_audience = i - zeros_cnt;
			ll value_if_taken_for_audience = 0;
			if (taken_audience < k)
			{
				value_if_taken_for_audience = old_dp[subset] + value_as_audience[i].first;
			}
			dp[subset] = max(max_if_taken_for_pos, value_if_taken_for_audience);
		}
		old_dp = dp;
	}
	cout << dp[0] << "\n";
	return 0;
}
