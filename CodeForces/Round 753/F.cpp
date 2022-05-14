#include <algorithm>
#include <iostream>
#include <vector>
#include <chrono>
using namespace std;
typedef long long ll;

pair<int, int> get_next_cell(int current_row, int current_col, const vector<string>& symbols)
{
	switch (symbols[current_row][current_col])
	{
	case 'L':
		return { current_row, current_col - 1 };
	case 'R':
		return { current_row, current_col + 1 };
	case 'U':
		return { current_row - 1, current_col};
	case 'D':
		return { current_row + 1, current_col };
	}
}

bool is_valid_cell(pair<int, int> cell, const vector<string>& symbols)
{
	int n = symbols.size();
	int m = symbols[0].size();
	int row = cell.first;
	int col = cell.second;
	if (row < 0 || row >= n || col < 0 || col >= m)
		return false;
	return true;
}

void fill_cells_from(const vector<string>& symbols, vector<vector<int>>& dp, int row, int col, int value)
{
	pair<int, int> start_cell = { row,col };
	dp[row][col] = value;
	auto current_cell = get_next_cell(row, col, symbols);
	while (current_cell != start_cell)
	{
		dp[current_cell.first][current_cell.second] = value;
		current_cell = get_next_cell(current_cell.first, current_cell.second, symbols);
	}
}

void dfs_fill_cycles(const vector<string>& symbols, vector<vector<int>>& dp, int row, int col, int time, vector<vector<int>>& time_visited, vector<vector<bool>>& ever_visited)
{
	time_visited[row][col] = time;
	auto next_cell = get_next_cell(row, col, symbols);
	if (is_valid_cell(next_cell,symbols) && !ever_visited[next_cell.first][next_cell.second])
	{
		if (time_visited[next_cell.first][next_cell.second] != -1)
		{
			int cycle_length = time - time_visited[next_cell.first][next_cell.second] + 1;
			fill_cells_from(symbols, dp, next_cell.first, next_cell.second, cycle_length);
		}
		else
		{
			dfs_fill_cycles(symbols, dp, next_cell.first, next_cell.second, time + 1, time_visited, ever_visited);
		}
	}
	ever_visited[row][col] = 1;
}

void fill_cycles(const vector<string>& symbols, vector<vector<int>>& dp)
{
	int n = symbols.size();
	int m = symbols[0].size();
	vector<vector<int>> time_visited(n, vector<int>(m, -1));
	vector<vector<bool>> ever_visited(n, vector<bool>(m, false));
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if (!ever_visited[i][j])
			{
				dfs_fill_cycles(symbols, dp, i, j, 0, time_visited, ever_visited);
			}
		}
	}
}

ll dfs(const vector<string>& symbols, int row, int col, vector<vector<int>>& dp, vector<vector<bool>>& visited)
{
	visited[row][col] = 1;
	auto next_cell = get_next_cell(row, col, symbols);
	int dist = 1;
	if (is_valid_cell(next_cell,symbols))
	{
		if (dp[next_cell.first][next_cell.second] != -1)
			dist = dp[next_cell.first][next_cell.second] + 1;
		else
			dist = dfs(symbols, next_cell.first, next_cell.second, dp, visited) + 1;
		
	}
	visited[row][col] = 0;
	dp[row][col] = dist;
	return dist;
}

string rand_str(int len)
{
	string s(len, ' ');
	vector<char> c = { 'L','R','U','D' };
	for (int i = 0; i < len; i++)
		s[i] = c[rand() % 4];
	return s;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	srand(time(0));
	
	int test_cnt; cin >> test_cnt;
	while (test_cnt--)
	{
		//int n, m; cin >> n >> m;
		int n = 2000, m = 2000;
		vector<string> symbols(n,rand_str(m));
		//for (int i = 0; i < n; i++)
		//	cin >> symbols[i];

		vector<vector<int>> dp(n, vector<int>(m,-1));
		fill_cycles(symbols, dp);
		vector<vector<bool>> visited(n, vector<bool>(m, false));
		
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < m; j++)
			{
				if (dp[i][j] == -1)
				{
					dfs(symbols, i, j, dp, visited);
				}
			}
		}

		int max_val = 0;
		int max_row = -1, max_col = -1;
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < m; j++)
			{
				if (dp[i][j] > max_val)
				{
					max_row = i;
					max_col = j;
					max_val = dp[i][j];
				}
			}
		}
		cout << max_row + 1 << " " << max_col + 1 << " " << max_val << "\n";
	}

	return 0;
}