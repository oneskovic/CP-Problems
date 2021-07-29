#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

bool can_fit_in_column(int start_row, int end_row, int column, const vector<vector<int>>& first_previous_block)
{
	return first_previous_block[end_row][column] < start_row;
}

int main()
{
	freopen("fortmoo.in", "r", stdin);
	freopen("fortmoo.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n, m; cin >> n >> m;
	vector<vector<bool>> is_blocked(n, vector<bool>(m));
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			char c; cin >> c;
			is_blocked[i][j] = (c == 'X');
		}
	}
	vector<vector<int>> first_previous_blocked(n, vector<int>(m)); // First previous block in a column
	for (int col = 0; col < m; col++)
	{
		int prev_block = -1;
		for (int row = 0; row < n; row++)
		{
			if (is_blocked[row][col])
				prev_block = row;
			first_previous_blocked[row][col] = prev_block;
		}
	}

	int max_area = -1;
	for (int start_row = 0; start_row < n; start_row++)
	{
		for (int end_row = start_row; end_row < n; end_row++)
		{
			int left_col = 0, right_col = 0;
			while (left_col < m && right_col < m)
			{
				while (left_col < m && !can_fit_in_column(start_row, end_row, left_col, first_previous_blocked))
				{
					left_col++;
					right_col = left_col;
				}
				int rightmost_fit = right_col;
				while (right_col < m && !is_blocked[start_row][right_col] && !is_blocked[end_row][right_col])
				{
					if (can_fit_in_column(start_row, end_row, right_col, first_previous_blocked))
					{
						rightmost_fit = right_col;
					}
					right_col++;
				}
				if (left_col < m && rightmost_fit<m && can_fit_in_column(start_row,end_row,left_col,first_previous_blocked) &&
					can_fit_in_column(start_row,end_row,rightmost_fit,first_previous_blocked))
				{
					int area = (end_row - start_row + 1) * (rightmost_fit - left_col + 1);
					max_area = max(max_area, area);
				}
				left_col = right_col + 1;
				right_col = left_col;
			}
		}
	}
	cout << max_area << "\n";
	return 0;
}