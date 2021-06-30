#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

bool is_valid_cell(int row, int col, int n, int m)
{
	return !(row < 0 || col < 0 || row >= n || col >= m);
}

vector<pair<int, int>> valid_neighbors(int row, int col, int n, int m)
{
	vector<int> drow = { 0,0,-1,1 };
	vector<int> dcol = { -1,1,0,0 };
	vector<pair<int, int>> neighbors;
	for (int i = 0; i < 4; i++)
	{
		int new_row = row + drow[i];
		int new_col = col + dcol[i];
		if (is_valid_cell(new_row,new_col,n,m))
		{
			neighbors.emplace_back(new_row, new_col);
		}
	}
	return neighbors;
}

void print_vector(const vector<vector<int>>& v)
{
	for (auto row: v)
	{
		for (auto col: row)
		{
			if (col == 0)
			{
				cout << 'R';
			}
			else
				cout << 'W';
		}
		cout << "\n";
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int test_cnt; cin >> test_cnt;
	while (test_cnt--)
	{
		int n, m; cin >> n >> m;
		vector<vector<int>> colors(n, vector<int>(m,2));
		pair<int, int> non_empty_cell;
		for (int i = 0; i < n; i++)
		{
			string row; cin >> row;
			for (int j = 0; j < m; j++)
			{
				if (row[j] == 'R')
				{
					colors[i][j] = 0;
					non_empty_cell = { i,j };
				}
				else if (row[j] == 'W')
				{
					colors[i][j] = 1;
					non_empty_cell = { i,j };
				}
			}
		}

		vector<vector<bool>> visited(n, vector<bool>(m));
		queue<pair<int, pair<int,int>>> bfs_queue;
		bfs_queue.push({ colors[non_empty_cell.first][non_empty_cell.second],non_empty_cell });
		visited[non_empty_cell.first][non_empty_cell.second] = 1;
		bool failed = false;
		while (!bfs_queue.empty() && !failed)
		{
			bool current_color = bfs_queue.front().first;
			int row = bfs_queue.front().second.first;
			int col = bfs_queue.front().second.second;
			bfs_queue.pop();
			auto neighbors = valid_neighbors(row, col, n, m);
			for (auto neighbor: neighbors)
			{
				int neighbor_row = neighbor.first, neighbor_col = neighbor.second;
				bool neighbor_color = !current_color;
				if (colors[neighbor_row][neighbor_col] == 2)
				{
					colors[neighbor_row][neighbor_col] = neighbor_color;
				}
				else if (colors[neighbor_row][neighbor_col] != neighbor_color)
				{
					failed = true;
					break;
				}
				if (!visited[neighbor_row][neighbor_col])
				{
					bfs_queue.push({ neighbor_color, { neighbor_row,neighbor_col } });
					visited[neighbor_row][neighbor_col] = 1;
				}
			}
		}
		if (!failed)
		{
			cout << "YES\n";
			print_vector(colors);
		}
		else
			cout << "NO\n";
	}
	return 0;
}