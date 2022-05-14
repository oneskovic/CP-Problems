#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	
	int test_cnt; cin >> test_cnt;
	while (test_cnt--)
	{
		int n, m; cin >> n >> m;
		int r, c; cin >> r >> c;

		vector<vector<bool>> board(n, vector<bool>(m));
		bool black_exists = 0;
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < m; j++)
			{
				char c; cin >> c;
				if (c == 'W')
					board[i][j] = 0;
				else
				{
					board[i][j] = 1;
					black_exists = 1;
				}
			}
		}
		
		r--; c--;
		if (board[r][c])
		{
			cout << 0 << "\n";
			continue;
		}

		bool black_in_row_or_col = 0;
		for (int row = 0; row < n; row++)
		{
			if (board[row][c])
			{
				black_in_row_or_col = 1;
			}
		}
		for (int col = 0; col < m; col++)
		{
			if (board[r][col])
			{
				black_in_row_or_col = 1;
			}
		}
		if (black_in_row_or_col)
		{
			cout << 1 << "\n";
		}
		else if (black_exists)
		{
			cout << 2 << "\n";
		}
		else
		{
			cout << -1 << "\n";
		}
	}

	return 0;
}