#include <algorithm>
#include <iostream>
#include <limits.h>
#include <iomanip>
#include <vector>
#include <string>
using namespace std;
typedef long long ll;

vector<ll> bruteforce(int n, int cnt_to_satisfy, vector<pair<int, int>> queries)
{
	for (int i = 0; i < queries.size(); i++)
		swap(queries[i].first, queries[i].second);
	sort(queries.begin(), queries.end());
	for (int i = 0; i < queries.size(); i++)
		swap(queries[i].first, queries[i].second);
	
	vector<int> query_masks(queries.size());
	for (int i = 0; i < queries.size(); i++)
	{
		int mask = 0;
		int tmp_shift = 1 << (queries[i].first-1);
		for (int j = queries[i].first; j <= queries[i].second; j++)
		{
			mask |= tmp_shift;
			tmp_shift <<= 1;
		}
		query_masks[i] = mask;
	}

	vector<ll> dp_row(n);
	for (int i = 1; i < (1<<n); i++)
	{
		int cnt_satisfied = 0;
		for (int mask: query_masks)
		{
			if (cnt_satisfied == cnt_to_satisfy)
				break;
			
			if (mask & i)
				cnt_satisfied++;
			else
				break;
		}
		int last_1_pos = -1;
		int mask = 1;
		for (int j = 0; j < 20; j++)
		{
			if (i & mask)
				last_1_pos = j;
			mask <<= 1;
		}
		if (cnt_satisfied == cnt_to_satisfy)
		{
			dp_row[last_1_pos]++;
		}
	}
	return dp_row;
}

void debug(const vector<vector<ll>>& dp, vector<pair<int,int>> queries)
{
	int n = dp[0].size();
	int query_cnt = queries.size();
	auto correct_dp = vector<vector<ll>>(query_cnt + 1, vector<ll>());
	for (int i = 0; i <= query_cnt; i++)
		correct_dp[i] = bruteforce(n, i, queries);
	for (auto row : dp)
	{
		for (int x : row)
		{
			cout << setw(3) << setfill('0') << x << " ";
		}
		cout << "\n";
	}
	cout << "\n";
	for (auto row : correct_dp)
	{
		for (int x : row)
		{
			cout << setw(3) << setfill('0') << x << " ";
		}
		cout << "\n";
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	const ll mod = 1e9 + 7;
	int n, query_cnt; cin >> n >> query_cnt;
	
	vector<pair<int, int>> queries;

	for (int i = 0; i < query_cnt; i++)
	{
		int l, r; cin >> l >> r;
		queries.push_back({ l,r });
	}

	for (int i = 0; i < queries.size(); i++)
		swap(queries[i].first, queries[i].second);
	sort(queries.begin(), queries.end());
	for (int i = 0; i < queries.size(); i++)
		swap(queries[i].first, queries[i].second);
	
	vector<ll> dp(n);
	ll x = 1;
	for (int i = 0; i < n; i++)
	{
		dp[i] = x;
		x <<= 1;
		x %= mod;
	}
	int last_zero_pos = -1;
	int last_add_pos = -1;
	ll sum = 0;
	for (int i = 0; i < queries.front().first-1; i++)
	{
		sum += dp[i];
		last_add_pos = i;
	}
	sum %= mod;
	for (int i = 1; i <= query_cnt; i++)
	{
		int next_r = i < query_cnt ? queries[i].second : n;
		int l = queries[i-1].first - 1;
		int r = queries[i-1].second - 1;
		
		for (int j = max(l,last_add_pos+1); j <= r; j++)
		{
			sum += dp[j];
			last_add_pos = j;
		}
		sum %= mod;
		for (int j = min(l,last_zero_pos+1); j < l; j++)
		{
			sum -= dp[j];
			last_zero_pos = j;
		}
		sum %= mod;

		ll temp_sum = sum;
		for (int j = r+1; j < min(next_r,n); j++)
		{
			dp[j] = temp_sum;
			temp_sum <<= 1;
			temp_sum %= mod;
		}
	}
	cout << (sum%mod + mod)%mod << "\n";

	

	
	return 0;
}