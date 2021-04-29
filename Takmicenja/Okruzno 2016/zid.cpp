#include <algorithm>
#include <iostream>
#include <vector>
#include <random>
#include <time.h>
#include <map>
#include <set>
#include <queue>
using namespace std;
typedef long long ll;

map<ll, ll> make_sufixes(const map<ll, vector<pair<ll, ll>>>& points)
{
	map<ll, ll> suffix_max;
	ll current_max = 0;
	for (auto it = points.rbegin(); it != points.rend(); it++)
	{
		suffix_max[it->first] = current_max;
		current_max = max(current_max, it->second[0].second);
		for (auto p : it->second)
		{
			current_max = max(p.second, current_max);
		}
	}
	return suffix_max;
}
/*
map<ll, ll> make_prefixes(const map<ll, vector<pair<ll, ll>>>& points)
{
	map<ll, ll> prefix_max;
	ll current_max = 0;
	for (auto it = points.begin(); it != points.end(); it++)
	{
		sort(it->second.begin(), it->second.end());
		current_max = max(current_max, it->second[0].second);
		for (auto p : it->second)
		{
			current_max = max(p.second, current_max);
		}
		prefix_max[it->first] = current_max;
	}
	return prefix_max;
}
*/
ll solve(const vector<vector<ll>>& points, ll wall_price)
{
	int n = points.size();
	map<ll, vector<pair<ll, ll>>> points_by_x, points_by_y;
	for (int i = 0; i < n; i++)
	{
		ll x = points[i][0], y = points[i][1], w = points[i][2];
		x = abs(x);
		y = abs(y);
		points_by_x[x].push_back({ y,w });
		points_by_y[y].push_back({ x,w });
	}

	auto suffix_by_x = make_sufixes(points_by_x);
	auto suffix_by_y = make_sufixes(points_by_y);

	ll solution = LLONG_MAX;
	
	set<pair<ll,ll>> two_largest_points;
	two_largest_points.insert({ 0,0 });
	for (auto kvp : points_by_x)
	{
		for (auto p: kvp.second)
		{
			if (two_largest_points.size() > 2)
				two_largest_points.erase(two_largest_points.begin());
			
			two_largest_points.insert({ p.second, p.first });
		}

		// Either take just the point with largest weight

		vector<pair<ll,ll>> temp(two_largest_points.begin(),two_largest_points.end());
		sort(temp.begin(), temp.end(), greater<pair<ll,ll>>());
		ll current_height = temp[0].second;
		ll remaining_max = max(suffix_by_x[kvp.first], suffix_by_y[current_height]);

		ll current_price = wall_price * 4 * (kvp.first + current_height) + remaining_max;
		if (current_height == 0)
			current_price = wall_price * 4 * kvp.first + remaining_max;
		if (kvp.first == 0)
			current_price = wall_price * 4 * current_height + remaining_max;
		
		solution = min(solution, current_price);

		// Or take the point with largest weight and the point with largest weight between current x
		if (temp.size() > 1)
		{
			current_height = max(current_height, temp[1].second);
		}
		remaining_max = max(suffix_by_x[kvp.first], suffix_by_y[current_height]);

		current_price = wall_price * 4 * (kvp.first + current_height) + remaining_max;
		if (current_height == 0)
			current_price = wall_price * 4 * kvp.first + remaining_max;
		if (kvp.first == 0)
			current_price = wall_price * 4 * current_height + remaining_max;

		solution = min(solution, current_price);
	}
	vector<pair<ll, ll>> temp(two_largest_points.begin(), two_largest_points.end());
	sort(temp.begin(), temp.end(), greater<pair<ll, ll>>());

	return min(solution, temp[0].first);
}

ll brutus(const vector<vector<ll>>& points, ll wall_price)
{
	ll solution = LLONG_MAX;
	set<ll> all_dx, all_dy;
	for (int i = 0; i < points.size(); i++)
	{
		all_dx.insert(abs(points[i][0]));
		all_dy.insert(abs(points[i][1]));
	}
	for (ll dx: all_dx)
	{
		for (ll dy: all_dy)
		{
			ll max_of_rem = 0;
			for (auto other_point : points)
			{
				if (abs(other_point[0]) > dx || abs(other_point[1]) > dy)
				{
					max_of_rem = max(max_of_rem, other_point[2]);
				}
			}
			ll cost = max_of_rem + 4 * (dx + dy) * wall_price;
			if (dx == 0)
			{
				cost = max_of_rem + 4 * dy * wall_price;
			}
			if (dy == 0)
			{
				cost = max_of_rem + 4 * dx * wall_price;
			}
			solution = min(solution, cost);
		}
	}
	return solution;
}

void test(int test_cnt)
{
	srand(time(0));
	ll min_x = -3, max_x = 3, min_y = -3, max_y = 3;
	ll max_w = 10;
	for (int t = 0; t < test_cnt; t++)
	{
		ll point_cnt = rand() % 10 + 1;
		ll wall_price = rand() % 10 + 1;
		vector<vector<ll>> points(point_cnt,vector<ll>(3));
		for (size_t i = 0; i < point_cnt; i++)
		{
			points[i][0] = rand() % (max_x - min_x) + min_x;
			points[i][1] = rand() % (max_y - min_y) + min_y;
			points[i][2] = rand() % max_w + 1;
		}
		points.push_back({ 0,0,0 });

		ll s1 = solve(points, wall_price);
		ll s2 = brutus(points, wall_price);
		if (s1 != s2)
		{
			cout << "WA\n";
			solve(points, wall_price);
		}
		else
			cout << t << " OK\n";
	}

	
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	//test(10000000);

	ll n, c; cin >> n >> c;
	vector<vector<ll>> points(n,vector<ll>(3));
	for (size_t i = 0; i < n; i++)
	{
		cin >> points[i][0] >> points[i][1] >> points[i][2];
	}
	points.push_back({ 0,0,0 });
	auto s1 = solve(points, c);
	auto s2 = brutus(points, c);
	cout << solve(points, c);
	
	return 0;
}
