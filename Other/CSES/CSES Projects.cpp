#include <algorithm>
#include <iostream>
#include <vector>
#include <map>
using namespace std;
typedef long long ll;

struct interval
{
	int l, r;
	ll val;
};

void compress_coords(vector<interval>& intervals)
{
	vector<int> interval_points; interval_points.reserve(2 * intervals.size());
	for (int i = 0; i < intervals.size(); i++)
	{
		interval_points.push_back(intervals[i].l);
		interval_points.push_back(intervals[i].r);
	}

	sort(interval_points.begin(), interval_points.end());
	interval_points.erase(unique(interval_points.begin(), interval_points.end()), interval_points.end());
	map<int, int> compressed_coords;
	for (int i = 0; i < interval_points.size(); i++)
		compressed_coords[interval_points[i]] = i;

	for (int i = 0; i < intervals.size(); i++)
	{
		intervals[i].l = compressed_coords[intervals[i].l];
		intervals[i].r = compressed_coords[intervals[i].r];
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n; cin >> n;
	vector<ll> dp(2*n);
	vector<interval> intervals(n);
	for (int i = 0; i < n; i++)
		cin >> intervals[i].l >> intervals[i].r >> intervals[i].val;

	compress_coords(intervals);
	vector<vector<interval>> intervals_by_right_point(2*n, vector<interval>());
	for (int i = 0; i < intervals.size(); i++)
	{
		intervals_by_right_point[intervals[i].r].push_back(intervals[i]);
	}

	for (int i = 0; i < 2*n; i++)
	{
		if (i > 0)
			dp[i] = dp[i - 1];
		for (auto& x : intervals_by_right_point[i])
		{
			ll new_val = 0;
			if (x.l > 0)
				new_val = dp[x.l - 1] + x.val;
			else
				new_val = x.val;

			dp[i] = max(dp[i], new_val);
		}
	}
	
	cout << *max_element(dp.begin(), dp.end());
	return 0;
}