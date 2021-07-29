#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;

bool is_valid_cell(int row, int col, int n, int m)
{
	return (row >= 0 && col >= 0 && row < n && col < m);
}

void mark_neighbors(int row, int col, vector<vector<int>>& table)
{
	vector<int> dcol = { -1,-1,-1,0,0,0,1,1,1 }, drow = {1,0,-1,1,0,-1,1,0,-1};
	for (int i = 0; i < dcol.size(); i++)
	{
		int nrow = row + drow[i];
		int ncol = col + dcol[i];
		if (is_valid_cell(nrow,ncol,table.size(),table[0].size()))
		{
			table[nrow][ncol] = -1;
		}
	}
}

int fill_table(int start_row, int start_col, vector<vector<int>>& table)
{
	int h = table.size(), w = table[0].size();
	
	int cnt = 0;
	for (int col = 0; col < w; col++)
	{
		if (table[0][col] != -1)
		{
			mark_neighbors(0, col,table);
			table[0][col] = 1;
			cnt++;
		}
	}
	for (int row = 1; row < h; row++)
	{
		if (table[row][w-1] != -1)
		{
			mark_neighbors(row,w-1, table);
			table[row][w - 1] = 1;
			cnt++;
		}	
	}
	for (int col = w - 2; col >= 0; col--)
	{
		if (table[h-1][col] != -1)
		{
			mark_neighbors(h - 1, col, table);
			table[h - 1][col] = 1;
			cnt++;
		}
	}
	for (int row = h - 2; row > 0; row--)
	{
		if (table[row][0] != -1)
		{
			mark_neighbors(row, 0, table);
			table[row][0] = 1;
			cnt++;
		}
	}
	return cnt;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	int test_cnt; cin >> test_cnt;
	while (test_cnt--)
	{
		int h, w; cin >> h >> w;
		vector<vector<int>> clear_table(h, vector<int>(w));
		vector<vector<int>> table(h, vector<int>(w));
		auto best_table = table;
		int best_result = -1;
		for (int col = 0; col < w; col++)
		{
			int res = fill_table(0, col, table);
			if (res > best_result)
			{
				best_table = table;
				best_result = res;
			}
			table = clear_table;
		}
		for (int row = 0; row < h; row++)
		{
			int res = fill_table(row, 0, table);
			if (res > best_result)
			{
				best_table = table;
				best_result = res;
			}
			table = clear_table;
		}

		
		
		for (auto& row: best_table)
		{
			for (int i: row)
			{
				if (i == 1)
				{
					cout << 1;
				}
				else
					cout << 0;
			}
			cout << "\n";
		}
		cout << "\n";
	}
	return 0;
}