#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

bool exists_path(const vector<vector<int>>& subgrid)
{
	if (subgrid[0][2] == subgrid[1][2])
		return true;
	if (subgrid[1][1] == subgrid[1][2] || subgrid[1][1] == subgrid[2][1])
		return true;
	if (subgrid[2][0] == subgrid[2][1])
		return true;
	return false;
}
vector<pair<int, int>> position_map =
{
	{0,2},
	{1,1},
	{1,2},
	{2,0},
	{2,1}
};
bool try_block(vector<vector<int>>& subgrid, int position, int remaining_flips)
{
	if (position == 5)
		return !exists_path(subgrid);

	auto row_col = position_map[position];
	if (try_block(subgrid, position + 1, remaining_flips))
	{
		return true;
	}
	else if (remaining_flips > 0)
	{
		bool current_val = subgrid[row_col.first][row_col.second];
		subgrid[row_col.first][row_col.second] = !current_val;
		bool can_block =  try_block(subgrid, position + 1, remaining_flips - 1);
		if (can_block)
			return true;
		subgrid[row_col.first][row_col.second] = current_val;	
		return false;
	}
	else
		return false;
}

vector<vector<vector<int>>> all_subgrids;

void generate(vector<vector<int>>& subgrid, int position)
{
	if (position == 5)
		all_subgrids.push_back(subgrid);
	else
	{
		auto row_col = position_map[position];
		subgrid[row_col.first][row_col.second] = 0;
		generate(subgrid, position + 1);
		subgrid[row_col.first][row_col.second] = 1;
		generate(subgrid, position + 1);
	}
}

int main()
{
	ios::sync_with_stdio(false);
	int test_count; cin >> test_count;
	for (size_t test_number = 0; test_number < test_count; test_number++)
	{
		int n; cin >> n;
		vector<vector<int>> grid(n);
		for (size_t row = 0; row < n; row++)
		{
			grid[row] = vector<int>(n);
			string row_str; cin >> row_str;
			for (size_t col = 0; col < n; col++)
				grid[row][col] = row_str[col] - '0';
		}
		vector<vector<int>> subgrid;
		for (size_t row = n-3; row <= n-1; row++)
		{
			vector<int> subrow;
			for (size_t col = n-3; col <= n-1; col++)
			{
				subrow.push_back(grid[row][col]);
			}
			subgrid.push_back(subrow);
		}
		auto og_subgrid = subgrid;
		try_block(subgrid, 0, 2);
		vector<pair<int, int>> solutions;
		for (size_t row = 0; row < 3; row++)
		{
			for (size_t col = 0; col < 3; col++)
			{
				if (subgrid[row][col] != og_subgrid[row][col])
					solutions.push_back({ row+n-3,col+n-3 });
			}
		}
		cout << solutions.size() << "\n";
		for (auto sol: solutions)
		{
			cout << sol.first+1 << " " << sol.second+1 << "\n";
		}

	}
	return 0;
}
