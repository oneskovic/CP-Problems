#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;

void print_row(const vector<bool>& row)
{
	for (auto x : row)
	{
		if (x)
			cout << "X";
		else
			cout << ".";
	}
	cout << "\n";
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int test_cnt; cin >> test_cnt;
	while (test_cnt--)
	{
		int n, k, r, c; cin >> n >> k >> r >> c;
		r--; c--;
		vector<vector<bool>> board(n, vector<bool>(n));
		int row_mod = 0;
		for (int row = 0; row < n; row++)
		{
			vector<bool> current_row(n);
			for (int col = 0; col < n; col++)
				board[row][col] = (col % k == row_mod);
			row_mod++;
			row_mod %= k;
		}
		if (!board[r][c])
		{
			int start_row = r - r % k;
			for (int row = start_row; row < start_row + k; row++)
			{
				if (board[row][c])
				{
					swap(board[row], board[r]);
					break;
				}
			}

			for (int i = 0; i < n/k; i++)
			{
				for (int row = start_row; row < start_row + k; row++)
				{
					print_row(board[row]);
				}
			}
		}
		else {

			for (const auto& row : board)
			{
				print_row(row);
			}
		}
	}

	return 0;
}
