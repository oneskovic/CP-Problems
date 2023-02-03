#include <algorithm>
#include <iostream>
#include <vector>
#include <limits.h>
using namespace std;
typedef long long ll;

struct point
{
	int x, y;
};

bool compare_x(const point& lhs, const point& rhs)
{
	return lhs.x < rhs.x;
}

int main()
{
	//freopen("split.in", "r", stdin);
	//freopen("split.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n; cin >> n;
	vector<point> points(n);
	for (int i = 0; i < n; i++)
		cin >> points[i].x >> points[i].y;

	sort(points.begin(), points.end(), compare_x);
	vector<int> prefix_max_y(n), suffix_max_y(n);
	vector<int> prefix_min_y(n), suffix_min_y(n);
	prefix_max_y[0] = points[0].y;
	prefix_min_y[0] = points[0].y;
	for (int i = 1; i < n; i++)
	{
		prefix_max_y[i] = max(prefix_max_y[i - 1], points[i].y);
		prefix_min_y[i] = min(prefix_min_y[i - 1], points[i].y);
	}

	suffix_max_y[n - 1] = points[n - 1].y;
	suffix_min_y[n - 1] = points[n - 1].y;
	for (int i = n - 2; i >= 0; i--)
	{
		suffix_max_y[i] = max(suffix_max_y[i + 1], points[i].y);
		suffix_min_y[i] = min(suffix_min_y[i + 1], points[i].y);
	}

	ll solution = LLONG_MAX;
	for (int i = 0, j = 0; i < n;)
	{
		while (j < n && points[j].x == points[i].x)
			j++;

		ll total_area = 0;
		ll w1 = points[i].x - points[0].x;
		ll h1 = prefix_max_y[j-1] - prefix_min_y[j-1];
		total_area += w1 * h1;

		if (j != n)
		{
			ll w2 = points.back().x - points[j].x;
			ll h2 = suffix_max_y[j] - suffix_min_y[j];
			total_area += w2 * h2;
		}
		solution = min(solution, total_area);
		i = j;
	}

	ll w = points.back().x - points[0].x;
	ll h = prefix_max_y.back() - prefix_min_y.back();
	cout << w*h - solution;
	return 0;
}