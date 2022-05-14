#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;

pair<vector<bool>,vector<ll>> cost_to_have_bit(ll number) 
{	
	ll mask = 1;
	ll sum_prev = 0;
	vector<ll> costs(61);
	vector<bool> sign(61);
	for (int i = 0; i <= 60; i++)
	{
		sum_prev += (number & mask);
		costs[i] = max(((ll)1 << i) - sum_prev, (ll)0);
		sign[i] = 1;
		if (sum_prev < number)
		{
			if (costs[i] > sum_prev + 1)
			{
				sign[i] = 0;
				costs[i] = sum_prev + 1;
			}
		}
			
		mask <<= 1;
	}
	return { sign,costs };
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n; cin >> n;
	vector<ll> elements(n);
	for (int i = 0; i < n; i++)
		cin >> elements[i];
	
	vector<pair<ll, int>> column_costs(61);
	auto new_values = vector<vector<ll>>(n, vector<ll>(61));
	for (int i = 0; i < n; i++)
	{
		auto r = cost_to_have_bit(elements[i]);
		vector<ll> temp = vector<ll>(61, elements[i]);
		for (int i = 0; i <= 60; i++)
		{
			if (r.first[i])
				temp[i] += r.second[i];
			else
				temp[i] -= r.second[i];
		}
		new_values[i] = temp;
		for (int col = 0; col <= 60; col++)
			if (column_costs[col].first < 1e13)
				column_costs[col].first += r.second[col];		
	}
	
	for (int col = 0; col <= 60; col++)
		column_costs[col].second = -col;
	sort(column_costs.begin(), column_costs.end());
	vector<int> best_cols;
	for (int i = 0; i <= 60; i++)
		if (column_costs[i].first == column_costs[0].first)
			best_cols.push_back(-column_costs[i].second);

	ll sol = LLONG_MAX;
	int j = 0;
	for (int c: best_cols)
	{
		int col_to_xor = c == 0 ? 1 : 0;
		int cost_to_change_bit = c == 0 ? 2 : 1;
		int cnt_ones = 0;
		ll mask = (ll)1 << col_to_xor;
		for (int i = 0; i < n; i++)
		{
			if (new_values[i][c] & mask)
			{
				cnt_ones++;
			}
		}
		ll res = column_costs[j].first;
		if (cnt_ones % 2 == 0)
			res += cost_to_change_bit;
		sol = min(res, sol);
		j++;
	}
	cout << sol << "\n";

	return 0;
}