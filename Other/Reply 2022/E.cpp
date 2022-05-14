#include <algorithm>
#include <iostream>
#include <limits.h>
#include <vector>
#include <queue>
#include <tuple>
using namespace std;
typedef long long ll;

struct line_stats
{
	int cnt_occupied, cnt_ships, cnt_max_consecutive_empty;
};
struct stats
{
	vector<line_stats> row_stats;
	vector<line_stats> col_stats;
};

bool check_line(const vector<line_stats>& v, const vector<line_stats>& limit)
{
	int n = v.size();
	for (int i = 0; i < n; i++)
	{
		if (v[i].cnt_ships > limit[i].cnt_ships)
			return false;
		if (v[i].cnt_occupied > limit[i].cnt_occupied)
			return false;
	}
	return true;
}

bool current_stats_ok(const stats& current_stats, const stats& limit)
{
	return check_line(current_stats.row_stats, limit.row_stats) && check_line(current_stats.col_stats, limit.col_stats);
}

bool is_in_board(int row, int col, const vector<vector<bool>>& board)
{
	int n = board.size();
	return row >= 0 && row < n&& col >= 0 && col < n;
}

bool any_neighbor_occupied(int row, int col, const vector<vector<bool>>& board)
{
	vector<int> drow = { -1,1,0,0 };
	vector<int> dcol = { 0,0,-1,1 };
	for (int i = 0; i < 4; i++)
	{
		int new_row = row + drow[i];
		int new_col = col + dcol[i];
		if (is_in_board(new_row, new_col,board) && board[new_row][new_col])
		{
			return true;
		}
	}
	return false;
}

bool can_place(const vector<vector<bool>>& board, int row, int col, int len, int drow, int dcol)
{
	int cnt_placed = 0;
	for (int i = 0; i < len && is_in_board(row,col,board); i++)
	{
		if (any_neighbor_occupied(row,col,board))
			return false;
		row += drow;
		col += dcol;
		cnt_placed++;
	}
	return cnt_placed == len;
}

void place(vector<vector<bool>>& board, stats& current_stats, int row, int col, int len, int drow, int dcol, bool new_val)
{
	int prev_row = -1;
	int prev_col = -1;
	int to_add = new_val ? 1 : -1;
	for (int i = 0; i < len; i++)
	{
		board[row][col] = new_val;
		if (prev_row != row)
			current_stats.row_stats[row].cnt_ships += to_add;
		if (prev_col != col)
			current_stats.col_stats[col].cnt_ships += to_add;

		current_stats.row_stats[row].cnt_occupied += to_add;
		current_stats.col_stats[col].cnt_occupied += to_add;

		prev_row = row;
		prev_col = col;
		row += drow;
		col += dcol;
	}
}

bool check_consecutive_spaces(const vector<vector<bool>>& board)
{
	return false;
}

bool check_line_done(const vector<line_stats>& v, const vector<line_stats>& limit)
{
	int n = v.size();
	for (int i = 0; i < n; i++)
	{
		if (v[i].cnt_ships != limit[i].cnt_ships)
			return false;
		if (v[i].cnt_occupied != limit[i].cnt_occupied)
			return false;
		if (v[i].cnt_max_consecutive_empty != limit[i].cnt_max_consecutive_empty)
			return false;
	}
	return true;
}

int max_consecutive_empty(const vector<vector<bool>>& board, int drow, int dcol, int row, int col)
{
	int n = board.size();
	int cnt_empty = !board[row][col];
	int max_cnt = -1;
	row += drow;
	col += dcol;
	for (int i = 1; i < n; i++)
	{
		if (!board[row][col])
		{
			cnt_empty++;
		}
		else
		{
			max_cnt = max(max_cnt, cnt_empty);
			cnt_empty = 0;
		}
		row += drow;
		col += dcol;
	}
	max_cnt = max(max_cnt, cnt_empty);
	return max_cnt;
}

bool check_done(stats& current_stats, const stats& limit, const vector<vector<bool>>& board)
{
	int n = board.size();
	for (int i = 0; i < n; i++)
		current_stats.row_stats[i].cnt_max_consecutive_empty = max_consecutive_empty(board, 0, 1, i, 0);
	for (int i = 0; i < n; i++)
		current_stats.col_stats[i].cnt_max_consecutive_empty = max_consecutive_empty(board, 1, 0, 0, i);
	
	return check_line_done(current_stats.row_stats, limit.row_stats) && check_line_done(current_stats.col_stats, limit.col_stats);
}

void print_board(const vector<vector<bool>>& b)
{
	for (auto row: b)
	{
		for (bool b: row)
		{
			cout << b ? "1 " : "0 ";
		}
		cout << "\n";
	}
	cout << "------------------------------------------\n";
}

bool solve(int row, int col, vector<vector<bool>>& board, stats& current_stats, const stats& limit, int min_len, int max_len)
{
	if (row == board.size())
	{
		return check_done(current_stats,limit,board);
	}
	int next_row = row;
	int next_col = col + 1;
	if (!is_in_board(next_row,next_col,board))
	{
		next_col = 0;
		next_row++;
	}
	if (board[row][col])
	{
		return solve(next_row, next_col, board, current_stats, limit, min_len, max_len);
	}
	vector<pair<int, int>> deltas = { {0,1},{1,0}};
	if (solve(next_row, next_col, board, current_stats, limit, min_len, max_len))
	{
		return true;
	}
	for (int l = min_len; l <= max_len; l++)
	{
		for (auto delta: deltas)
		{
			int drow = delta.first;
			int dcol = delta.second;
			
			if (can_place(board, row, col, l, drow, dcol))
			{
				place(board, current_stats, row, col, l, drow, dcol, 1);
				//print_board(board);
				if (solve(next_row, next_col, board, current_stats, limit, min_len, max_len))
					return true;
				else
					place(board, current_stats, row, col, l, drow, dcol, 0);
			}
		}
	}
	return false;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int test_cnt; cin >> test_cnt;
	while (test_cnt--)
	{
		int n; cin >> n;
		int lmin, lmax; cin >> lmin >> lmax;
		stats limits = { vector<line_stats>(n), vector<line_stats>(n) };
		for (int j = 0; j < 2; j++)
		{
			auto& line = j == 0 ? limits.col_stats : limits.row_stats;

			for (int i = 0; i < n; i++)
				cin >> line[i].cnt_occupied;
			for (int i = 0; i < n; i++)
				cin >> line[i].cnt_ships;
			for (int i = 0; i < n; i++)
				cin >> line[i].cnt_max_consecutive_empty;
		}
		stats current_stats = { vector<line_stats>(n), vector<line_stats>(n) };
		vector<vector<bool>> board(n, vector<bool>(n));
		solve(0, 0, board, current_stats, limits, lmin, lmax);
		print_board(board);
	}


	return 0;
}