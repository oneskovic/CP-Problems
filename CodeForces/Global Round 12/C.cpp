#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

bool should_change_cell(const vector<string>& board, int row, int col)
{
	vector<vector<int>> dxs = { {-2,-1,0},{-1,0,1},{0,1,2} };
	vector<vector<int>> dys = { {-2,-1,0}, {-1,0,1},{0,1,2} };
	for (auto deltas: dxs)
	{
		int countX = 0;
		for (size_t i = 0; i < 3; i++)
		{
			int cx = col + deltas[i];
			if (cx >= 0 && cx < board.size())
			{
				countX += board[row][cx] == 'X' ? 1 : 0;
			}
			else
				break;
		}
		if (countX == 3)
			return true;
	}
	for (auto deltas : dys)
	{
		int countX = 0;
		for (size_t i = 0; i < 3; i++)
		{
			int cy = row + deltas[i];
			if (cy >= 0 && cy < board.size())
			{
				countX += board[cy][col] == 'X' ? 1 : 0;
			}
			else
				break;
		}
		if (countX == 3)
			return true;
	}
}

void solve_board(vector<string>& board)
{
	int n = board.size();
	int delta = 0;
	for (size_t row = 0; row < n; row++)
	{
		for (size_t col = delta; col < n; col+=3)
		{
			if (should_change_cell(board,row,col))
			{
				board[row][col] = 'O';
			}
		}
		delta++;
		delta %= 3;
	}
}

int main()
{
	int test_count; cin >> test_count;
	for (size_t test_no = 0; test_no < test_count; test_no++)
	{
		int n; cin >> n;
		vector<string> board(n);
		for (size_t i = 0; i < n; i++)
			cin >> board[i];
		
		solve_board(board);

		for (size_t i = 0; i < n; i++)
			cout << board[i] << "\n";
	}
	return 0;
}