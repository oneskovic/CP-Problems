#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
#define ll long long

struct point
{
	int x, y;
};

class subarray_sum_2d
{
public:
	subarray_sum_2d(const vector<vector<int>>& elements);
	ll sum(int upper_left_row, int upper_left_col, int bottom_right_row, int bottom_right_col);
private:
	vector<vector<ll>> prefixes;
};

int y_position_to_row(int y, int n)
{
	return (n - 1 - y);
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n; cin >> n;
	vector<point> points(n);
	for (size_t i = 0; i < n; i++)
		cin >> points[i].x >> points[i].y;

	sort(points.begin(), points.end(), [](const point& lhs, const point& rhs) {return lhs.y < rhs.y; });
	for (size_t i = 0; i < n; i++)
		points[i].y = i;

	sort(points.begin(), points.end(), [](const point& lhs, const point& rhs) {return lhs.x < rhs.x; });
	for (size_t i = 0; i < n; i++)
		points[i].x = i;

	vector<vector<int>> mapped_points(n, vector<int>(n));
	for (int i = 0; i < n; i++)
	{
		int row = y_position_to_row(points[i].y, n);
		int col = points[i].x;
		mapped_points[row][col] = 1;
	}
	auto sum_2d = subarray_sum_2d(mapped_points);

	ll solution = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = i+1; j < n; j++)
		{
			int x_left = points[i].x;
			int x_right = points[j].x;
			int y_bottom = min(points[i].y, points[j].y);
			int y_top = max(points[i].y, points[j].y);
			
			ll points_above = sum_2d.sum(y_position_to_row(n, n), x_left, y_position_to_row(y_top, n), x_right);
			ll points_below = sum_2d.sum(y_position_to_row(y_bottom, n), x_left, y_position_to_row(0, n), x_right);
			solution += points_above * points_below;
		}
	}
	solution += n + 1;
	cout << solution;
	return 0;
}

subarray_sum_2d::subarray_sum_2d(const vector<vector<int>>& elements)
{
	int row_count = elements.size();
	int col_count = elements[0].size();
	prefixes = vector<vector<ll>>(row_count, vector<ll>(col_count));

	prefixes[0][0] = elements[0][0];

	// Fill zeroth row
	for (int col = 1; col < row_count; col++)
		prefixes[0][col] = prefixes[0][col - 1] + elements[0][col];
	
	// Fill zeroth column
	for (int row = 1; row < col_count; row++)
		prefixes[row][0] = prefixes[row - 1][0] + elements[row][0];
	
	for (int row = 1; row < row_count; row++)
	{
		for (int col = 1; col < col_count; col++)
		{
			ll top_prefix = prefixes[row - 1][col];
			ll left_prefix = prefixes[row][col - 1];
			ll overlap = prefixes[row - 1][col - 1];
			prefixes[row][col] = elements[row][col] + top_prefix + left_prefix - overlap;
		}
	}
}

ll subarray_sum_2d::sum(int upper_left_row, int upper_left_col, int bottom_right_row, int bottom_right_col)
{
	ll sum = prefixes[bottom_right_row][bottom_right_col];
	ll left_prefix = upper_left_col > 0 ? prefixes[bottom_right_row][upper_left_col - 1] : 0;
	ll top_prefix = upper_left_row > 0 ? prefixes[upper_left_row - 1][bottom_right_col] : 0;
	ll overlap = upper_left_col > 0 && upper_left_row > 0 ? prefixes[upper_left_row - 1][upper_left_col - 1] : 0;
	return sum - left_prefix - top_prefix + overlap;
}
