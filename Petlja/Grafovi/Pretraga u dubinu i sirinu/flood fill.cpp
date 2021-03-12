#include <algorithm>
#include <iostream>
#include <string>
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

void add_neighbors(int row, int col, const vector<vector<bool>>& board, const vector<vector<bool>>& visited, queue<pair<int, int>>& bfs_queue)
{
	vector<int> d_row = { 0,0,-1,1 };
	vector<int> d_col = { -1,1,0,0 };
	for (size_t i = 0; i < 4; i++)
	{
		int new_row = row + d_row[i];
		int new_col = col + d_col[i];
		if (is_valid_cell(new_row, new_col, board) && !visited[new_row][new_col] && board[row][col] == board[new_row][new_col])
		{
			bfs_queue.emplace(new_row, new_col);
		}
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n, m; cin >> n >> m;
	vector<vector<bool>> board(n, vector<bool>(m));
	auto visited = board;

	for (size_t i = 0; i < n; i++)
	{
		string row; cin >> row;
		for (size_t j = 0; j < m; j++)
		{
			board[i][j] = (row[j] == '.' ? 1 : 0);
		}
	}

	int flood_row, flood_col; cin >> flood_row >> flood_col;
	char temp; cin >> temp;
	bool flood_color = (temp == '.' ? 1 : 0);

	queue<pair<int, int>> bfs_queue;
	bfs_queue.emplace(flood_row, flood_col);
	while (!bfs_queue.empty())
	{
		int current_row = bfs_queue.front().first;
		int current_col = bfs_queue.front().second;
		bfs_queue.pop();
		visited[current_row][current_col] = true;
		add_neighbors(current_row, current_col, board, visited, bfs_queue);
		board[current_row][current_col] = flood_color;
	}

	for (size_t i = 0; i < n; i++)
	{
		for (size_t j = 0; j < m; j++)
		{
			cout << (board[i][j] ? '.' : 'x');
		}
		cout << "\n";
	}
	return 0;
}