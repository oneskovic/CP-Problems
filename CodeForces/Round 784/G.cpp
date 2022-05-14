#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;

void print_grid(const vector<string>& grid)
{
	for (auto row: grid)
		cout << row << "\n";
	cout << "\n";
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int test_cnt; cin >> test_cnt;
	while (test_cnt--)
	{
		int n, m; cin >> n >> m;
		vector<string> grid(n);
		vector<vector<bool>> is_fixed(n, vector<bool>(m,0));
		for (int i = 0; i < n; i++)
		{
			cin >> grid[i];
			for (int j = 0; j < m; j++)
			{
				if (grid[i][j] == 'o')
					is_fixed[i][j] = 1;
			}
		}
		for (int col = 0; col < m; col++)
		{
			int prev_fixed_row = n;
			for (int row = n - 1; row >= 0; row--)
			{
				if (!is_fixed[row][col] && grid[row][col] == '*')
				{
					grid[row][col] = '.';
					grid[prev_fixed_row - 1][col] = '*';
					prev_fixed_row = prev_fixed_row-1;
				}
				else if (is_fixed[row][col])
				{
					prev_fixed_row = row;
				}
			}
		}
		print_grid(grid);
		
	}

	return 0;
}
