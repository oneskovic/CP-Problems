#include <algorithm>
#include <iostream>
#include <vector>
#include <climits>

using namespace std;

int y_coordinate_to_row(int y, int max_n)
{
	return (max_n - 1 - y);
}

void mark_all_rows(int bottom_row, int left_col, int top_row, int right_col, vector<vector<int>>& markers, int value = 1)
{
	for (int row = top_row; row <= bottom_row; row++)
	{
		markers[row][left_col] += value;
		if (right_col + 1 < markers[row].size())
		{
			markers[row][right_col + 1] -= value;
		}
	}
}

void fill_row(int row, const vector<vector<int>>& markers, vector<vector<int>>& values)
{
	int to_add = 0;
	for (int i = 0; i < markers[row].size(); i++)
	{
		to_add += markers[row][i];
		values[row][i] = to_add;
	}
}

vector<vector<int>> generate_values(const vector<vector<int>>& markers, int k, int bad_cell_value, int good_cell_value)
{
	int max_position = markers.size();

	auto values = vector<vector<int>>(max_position, vector<int>(max_position));
	for (int row = 0; row < max_position; row++)
	{
		fill_row(row, markers, values);
		for (int col = 0; col < max_position; col++)
		{
			if (values[row][col] == k)
				values[row][col] = bad_cell_value;
			else if (values[row][col] == k - 1)
				values[row][col] = good_cell_value;
			else if (values[row][col] < 0)
				values[row][col] = bad_cell_value;
			else
				values[row][col] = 0;
		}
	}
	return values;
}

vector<vector<vector<long long>>> napravi_sljivik(const vector<vector<int>>& values)
{
	int n = values.size();
	vector<vector<long long>> prefixes_1d(n, vector<long long>(n));

	// Generate 1d prefix sums per row
	for (int row = 0; row < n; row++)
	{
		long long sum = 0;
		for (int col = 0; col < n; col++)
		{
			sum += values[row][col];
			prefixes_1d[row][col] = sum;
		}
	}

	auto sljivik = vector<vector<vector<long long>>>(n, vector<vector<long long>>(n, vector<long long>(n)));
	for (int left_col = 0; left_col < n; left_col++)
	{
		for (int right_col = left_col; right_col < n; right_col++)
		{
			long long sljivik_sum = 0;
			for (int row = 0; row < n; row++)
			{
				long long left_prefix = left_col > 0 ? prefixes_1d[row][left_col-1] : 0;
				long long row_sum = prefixes_1d[row][right_col] - left_prefix;
				sljivik_sum += row_sum;
				sljivik[left_col][right_col][row] = sljivik_sum;
			}
		}
	}
	return sljivik;
}

// Returns a vector of size 4: left column, right column, top row, bottom row
vector<int> find_optimal_rectangle(const vector<vector<vector<long long>>>& sljivik)
{
	long long solution = LLONG_MIN;
	vector<int> optimal_rectangle = { -1,-1,-1,-1 };
	int n = sljivik.size();
	for (int left_col = 0; left_col < n; left_col++)
	{
		for (int right_col = left_col; right_col < n; right_col++)
		{
			long long min_prefix = 0;
			int top_row_when_min_prefix = 0;
			for (int bottom_row = 0; bottom_row < n; bottom_row++)
			{
				long long current_prefix = sljivik[left_col][right_col][bottom_row];
				long long current_optimal_sum =  current_prefix - min_prefix;
				if (solution < current_optimal_sum)
				{
					optimal_rectangle = { left_col, right_col, top_row_when_min_prefix, bottom_row };
					solution = current_optimal_sum;
				}
				if (current_prefix < min_prefix)
				{
					min_prefix = current_prefix;
					top_row_when_min_prefix = bottom_row+1;
				}
			}
		}
	}
	if (solution < 0)
	{
		return { -1,-1,-1,-1 };
	}
	return optimal_rectangle;
}

int main()
{
	//freopen("paintbarn.in", "r", stdin);
	//freopen("paintbarn.out", "w", stdout);

	ios::sync_with_stdio(false);
	cin.tie(0);

	int rectangle_count, k;
	cin >> rectangle_count >> k;
	int max_position = 200;
	vector<vector<int>> markers(max_position, vector<int>(max_position));
	for (size_t i = 0; i < rectangle_count; i++)
	{
		int bottom_row, left_col, top_row, right_col;
		
		int x1, y1, x2, y2;
		cin >> x1 >> y1 >> x2 >> y2;
		x2--; y2--;

		left_col = x1;
		bottom_row = y_coordinate_to_row(y1, max_position);

		right_col = x2;
		top_row = y_coordinate_to_row(y2, max_position);
		
		mark_all_rows(bottom_row, left_col, top_row, right_col, markers);
	}

	auto values = generate_values(markers, k, -1, 1);
	auto sljivik = napravi_sljivik(values);
	auto optimal_rect = find_optimal_rectangle(sljivik);
	int left_col1 = optimal_rect[0], right_col1 = optimal_rect[1], top_row1 = optimal_rect[2], bottom_row1 = optimal_rect[3];
	
	if (left_col1 >= 0)
	{
		for (int row = top_row1; row <= bottom_row1; row++)
			for (int col = left_col1; col <= right_col1; col++)
				values[row][col] = -(max_position * max_position * k);
	}
	
	sljivik = napravi_sljivik(values);
	optimal_rect = find_optimal_rectangle(sljivik);
	int left_col2 = optimal_rect[0], right_col2 = optimal_rect[1], top_row2 = optimal_rect[2], bottom_row2 = optimal_rect[3];

	// Mark properly
	if (bottom_row1 >= 0)
		mark_all_rows(bottom_row1, left_col1, top_row1, right_col1, markers);
	if (bottom_row2 >= 0)
		mark_all_rows(bottom_row2, left_col2, top_row2, right_col2, markers);
	
	values = generate_values(markers, k, 1, 0);
	long long solution = 0;
	for (int row = 0; row < max_position; row++)
		for (int col = 0; col < max_position; col++)
				solution += values[row][col];	
	cout << solution;

	return 0;
}
