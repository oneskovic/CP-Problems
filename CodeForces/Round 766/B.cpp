#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;
typedef long long ll;

struct cell
{
	int row, col;
};

bool is_valid_cell(cell c, int n, int m)
{
	return c.row >= 0 && c.row < n && c.col >= 0 && c.col < m;
}

vector<cell> get_neighbors(cell current_cell, const vector<vector<bool>>& visited)
{
	vector<int> d_row = { 0,0,-1,1 };
	vector<int> d_col = { -1,1,0,0 };
	vector<cell> neighbors;
	for (int i = 0; i < 4; i++)
	{
		cell new_cell = { current_cell.row + d_row[i], current_cell.col + d_col[i] };
		if (is_valid_cell(new_cell, visited.size(), visited[0].size()) && !visited[new_cell.row][new_cell.col])
		{
			neighbors.push_back(new_cell);
		}
	}
	return neighbors;
}

void temp(int n, int m)
{
	vector<vector<int>> res(n, vector<int>(m));
	for (int rahul_row = 0; rahul_row < n; rahul_row++)
	{
		for (int rahul_col = 0; rahul_col < m; rahul_col++)
		{
			int largest_dist_for_chosen = INT_MIN;
			for (int tina_row = 0; tina_row < n; tina_row++)
			{
				for (int tina_col = 0; tina_col < m; tina_col++)
				{
					largest_dist_for_chosen = max(largest_dist_for_chosen, abs(rahul_row - tina_row) + abs(rahul_col - tina_col));
				}
			}
			res[rahul_row][rahul_col] = largest_dist_for_chosen;
		}
	}
	for (auto row : res)
	{
		for (auto col : row)
		{
			cout << col << " ";
		}
		cout << "\n";
	}
}

int best_dist_for_cell(cell c, int n, int m)
{
	int d1 = abs(c.row - 0) + abs(c.col - 0);
	int d2 = abs(c.row - (n-1)) + abs(c.col - (m-1));
	int d3 = abs(c.row - 0) + abs(c.col - (m - 1));
	int d4 = abs(c.row - (n - 1)) + abs(c.col - 0);
	vector<int> sol = { d1,d2,d3,d4 };
	sort(sol.begin(), sol.end());
	return sol.back();
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	
	int test_cnt; cin >> test_cnt;
	while (test_cnt--)
	{
		int n, m; cin >> n >> m;
		temp(n, m);
		queue<pair<cell, int>> bfs_queue;
		vector<cell> best_cells;
		int min_dist = INT_MAX;
		for (int row = 0; row < n; row++)
		{
			for (int col = 0; col < m; col++)
			{
				cell current_cell = { row,col };
				int current_dist = best_dist_for_cell(current_cell, n, m);
				if (current_dist < min_dist)
				{
					best_cells.clear();
					best_cells = { current_cell };
					min_dist = current_dist;
				}
				else if (current_dist == min_dist)
				{
					best_cells.push_back(current_cell);
				}
			}
		}

		vector<vector<bool>> visited(n, vector<bool>(m));
		for (cell c: best_cells)
		{
			bfs_queue.emplace(c, min_dist);
			visited[c.row][c.col] = 1;
		}

		while (!bfs_queue.empty())
		{
			cell current_cell = bfs_queue.front().first;
			visited[current_cell.row][current_cell.col] = 1;
			int current_dist = bfs_queue.front().second;
			bfs_queue.pop();
			cout << current_dist << " ";
			for (cell neighbor: get_neighbors(current_cell, visited))
			{
				visited[neighbor.row][neighbor.col] = 1;
				bfs_queue.emplace(neighbor, current_dist + 1);
			}
		}
		cout << "\n";
	}
	

	return 0;
}