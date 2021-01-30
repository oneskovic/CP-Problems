#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

struct operation
{
	vector<pair<int, int>> positions;
};
ostream& operator<<(ostream& os, operation& op)
{
	for (auto position : op.positions)
	{
		os << position.first+1 << " " << position.second+1 << " ";
	}
	return os;
}


vector<operation> all_operations;

void select_and_flip(int count_zeros, int count_ones, vector<string>& table, int row, int col)
{
	// First pick the zeros / ones to flip, then commit the flips
	// Must be done this way because otherwise it would be possible to first flip a 0 to 1
	// And then flip the same 1 when flipping ones

	vector<pair<int, int>> positions_to_flip;
	// First pick which zeros to flip
	for (size_t i = 0; i <= 1; i++)
	{
		for (size_t j = 0; j <= 1; j++)
		{
			if (table[row+i][col+j] == '0' && count_zeros > 0)
			{
				count_zeros--;
				positions_to_flip.push_back({ row + i,col + j });
			}
		}
	}

	// Pick which ones to flip
	for (size_t i = 0; i <= 1; i++)
	{
		for (size_t j = 0; j <= 1; j++)
		{
			if (table[row + i][col + j] == '1' && count_ones > 0)
			{
				count_ones--;
				positions_to_flip.push_back({ row + i,col + j });
			}
		}
	}

	// Commit the flips
	for (auto position: positions_to_flip)
	{
		table[position.first][position.second] = table[position.first][position.second] == '0' ? '1' : '0';
	}
	all_operations.push_back({ positions_to_flip });
}

void solve_square(vector<string>& table, int row, int col)
{
	int count_ones = 0;
	for (size_t i = 0; i <= 1; i++)
		for (size_t j = 0; j <= 1; j++)
			if (table[row + i][col + j] == '1')
				count_ones++;
		
	
	if (count_ones == 4)
	{
		select_and_flip(0, 3, table, row, col);
		count_ones = 1;
	}
	if (count_ones == 1)
	{
		select_and_flip(2, 1, table, row, col);
		count_ones = 2;
	}
	if (count_ones == 2)
	{
		select_and_flip(2, 1, table, row, col);
		count_ones = 3;
	}
	if (count_ones == 3)
	{
		select_and_flip(0, 3, table, row, col);
	}
}

int main()
{
	int test_count; cin >> test_count;
	for (size_t test_no = 0; test_no < test_count; test_no++)
	{
		int n, m; cin >> n >> m;
		vector<string> table(n);
		for (size_t i = 0; i < n; i++)
			cin >> table[i];
		
		for (size_t i = 0; i < n-n%2; i+=2)
		{
			for (size_t j = 0; j < m-m%2; j+=2)
			{
				solve_square(table, i, j);
			}
			if (m%2 == 1)
			{
				solve_square(table, i, m - 2);
			}
		}
		if (n % 2 == 1)
		{
			for (size_t j = 0; j < m - m % 2; j += 2)
			{
				solve_square(table, n-2, j);
			}
			if (m % 2 == 1)
			{
				solve_square(table, n-2, m - 2);
			}
		}

		cout << all_operations.size() << "\n";
		for (auto op: all_operations)
			cout << op << "\n";
		all_operations.clear();
	}
	return 0;
}