#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

bool is_valid_cell(int row, int col, const vector<vector<bool>>& board)
{
	if (row < 0 || row >= board.size() || col < 0 || col >= board[0].size())
	{
		return false;
	}

	return true;
}

void add_neighbors(int row, int col, const vector<vector<bool>>& visited, queue<pair<int,int>>& bfs_queue)
{
	vector<int> d_row = { 0,0,-1,1 };
	vector<int> d_col = { -1,1,0,0 };
	for (size_t i = 0; i < 4; i++)
	{
		int new_row = row + d_row[i];
		int new_col = col + d_col[i];
		if (is_valid_cell(new_row, new_col, visited) && !visited[new_row][new_col])
		{
			bfs_queue.emplace(new_row, new_col);
		}
	}
}

int get_min_distance(int row, int col, const vector<vector<bool>>& board, const vector<vector<int>>& distances)
{
	vector<int> d_row = { 0,0,-1,1 };
	vector<int> d_col = { -1,1,0,0 };
	int min_dist = distances[row][col];
	for (size_t i = 0; i < 4; i++)
	{
		int new_row = row + d_row[i];
		int new_col = col + d_col[i];
		if (is_valid_cell(new_row, new_col, board))
		{
			min_dist = min(min_dist, distances[new_row][new_col] == INT_MAX ? INT_MAX : distances[new_row][new_col]+1);
		}
	}
	return min_dist;
}


int main()
{
	int n, m; cin >> n >> m;
	vector<vector<bool>> board(n, vector<bool>(m));
	vector<vector<int>> distances(n, vector<int>(m, INT_MAX));
	auto visited = board;

	queue<pair<int,int>> bfs_queue;
	for (size_t i = 0; i < n; i++)
	{
		for (size_t j = 0; j < m; j++)
		{
			bool b; cin >> b;
			board[i][j] = b;
			if (b)
			{
				bfs_queue.emplace(i, j);
				visited[i][j] = 1;
				distances[i][j] = 0;
			}
		}
	}

	int max_distance = -1;
	
	while (!bfs_queue.empty())
	{
		int row = bfs_queue.front().first;
		int col = bfs_queue.front().second;
		bfs_queue.pop();
		visited[row][col] = 1;

		add_neighbors(row, col, visited, bfs_queue);
		distances[row][col] = get_min_distance(row, col, board, distances);
		max_distance = max(max_distance, distances[row][col]);
	}

	cout << max_distance << "\n";
	return 0;
}