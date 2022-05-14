#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <queue>
using namespace std;
typedef long long ll;

struct cell 
{
	int row,col;
};

bool operator < (const pair<int, cell>& lhs, const pair<int, cell>& rhs)
{
	return lhs.first < rhs.first;
}

bool is_valid_cell(cell c, int n, int m)
{
	return c.row >= 0 && c.row < n&& c.col >= 0 && c.col < m;
}

vector<cell> get_neighbors(cell current_cell, const vector<vector<int>>& mat)
{
	int n = mat.size();
	int m = mat[0].size();
	vector<cell> neighbors;
	vector<int> drow = { 0,0,-1,1 };
	vector<int> dcol = { -1,1,0,0 };
	for (int i = 0; i < 4; i++)
	{
		cell new_cell = current_cell;
		new_cell.row += drow[i];
		new_cell.col += dcol[i];
		if (is_valid_cell(new_cell, n, m) && mat[new_cell.row][new_cell.col] == 0)
		{
			neighbors.push_back(new_cell);
		}
	}
	return neighbors;
}

void add_cell_to_queue(cell c, priority_queue<pair<int, cell>, vector<pair<int, cell>>, greater<pair<int, cell>>>& q, const vector<vector<int>>& mat)
{
	auto neighbor_cnt = get_neighbors(c, mat).size();
	q.push({ neighbor_cnt, c });
}

void bfs(vector<vector<int>>& mat, cell lab_cell)
{
	priority_queue<pair<int, cell>, vector<pair<int,cell>>, greater<pair<int,cell>>> bfs_queue;
	vector<vector<bool>> visited(mat.size(), vector<bool>(mat[0].size()));
	auto neighbors = get_neighbors(lab_cell, mat);
	for (cell c : neighbors)
	{
		add_cell_to_queue(c, bfs_queue, mat);
		visited[c.row][c.col] = 1;
	}
	visited[lab_cell.row][lab_cell.col] = 1;
	
	while (!bfs_queue.empty())
	{
		cell current_cell = bfs_queue.top().second;
		bfs_queue.pop();
		auto neighbors = get_neighbors(current_cell, mat);
		int count_free = neighbors.size();
		for (cell c: neighbors)
		{
			if (mat[c.row][c.col] == 2 || mat[c.row][c.col] == 3)
			{
				count_free--;
			}
			if (!visited[c.row][c.col])
			{
				add_cell_to_queue(c, bfs_queue, mat);
				visited[c.row][c.col] = 1;
			}
		}
		if (count_free < 2)
		{
			mat[current_cell.row][current_cell.col] = 3;
		}
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
		cell lab_cell = {-1,-1};
		vector<vector<int>> mat(n, vector<int>(m));
		for (int i = 0; i < n; i++)
		{
			string row; cin >> row;
			for (int j = 0; j < m; j++)
			{
				switch (row[j])
				{
				case '.':
					mat[i][j] = 0;
					break;
				case '#':
					mat[i][j] = 1;
					break;
				case 'L':
					mat[i][j] = 2;
					lab_cell = { i,j };
					break;
				}
			}
		}
		bfs(mat, lab_cell);
		vector<char> codes = { '.','#','L','+' };
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < m; j++)
			{
				cout << codes[mat[i][j]];
			}
			cout << "\n";
		}
	}

	return 0;
}