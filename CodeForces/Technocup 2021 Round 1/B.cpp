#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_set>
#include <unordered_map>
using namespace std;
#define ll long long

int main()
{
	ios::sync_with_stdio(false);
	int no_tests; cin >> no_tests;
	for (size_t i = 0; i < no_tests; i++)
	{
		int no_rows, no_cols; cin >> no_rows >> no_cols;
		for (size_t i = 0; i < no_rows-1; i++)
		{
			int a;
			for (size_t j = 0; j < no_cols; j++)
				cin >> a;
		}

		unordered_map<int, int> positions_row_to_find;
		unordered_set<int> row_to_find;
		for (size_t i = 0; i < no_cols; i++)
		{
			int element; cin >> element;
			positions_row_to_find[element] = i;
			row_to_find.insert(element);
		}

		vector<vector<int>> table(no_rows);
		for (size_t i = 0; i < no_rows; i++)
			table[i] = vector<int>(no_cols);
		
		for (size_t col = 0; col < no_cols; col++)
		{
			for (size_t row = 0; row < no_rows; row++)
				cin>>table[row][col];
		}

		int found_index = -1;
		for (size_t row = 0; row < no_rows; row++)
		{
			int found_elements = 0;
			for (size_t col = 0; col < no_cols; col++)
			{
				if (row_to_find.find(table[row][col]) != row_to_find.end())
					found_elements++;
			}
			if (found_elements == row_to_find.size())
			{
				found_index = row;
				break;
			}
		}

		vector<vector<int>> solution = table;
		for (size_t i = 0; i < no_cols; i++)
		{
			int correct_position = positions_row_to_find[table[found_index][i]];
			for (size_t row = 0; row < no_rows; row++)
			{
				solution[row][correct_position] = table[row][i];
			}
		}

		for (size_t row = 0; row < no_rows; row++)
		{
			for (size_t col = 0; col < no_cols; col++)
			{
				cout << solution[row][col] << " ";
			}
			cout << "\n";
		}
	}
	return 0;
}