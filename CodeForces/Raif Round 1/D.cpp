#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>
using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	int n; cin >> n;
	stack<int> unresolved_2_rows, unresolved_3_rows;
	int next_row = 1, next_col = 1;
	vector<pair<int, int>> solutions;
	for (size_t i = 0; i < n; i++)
	{
		int no_hits; cin >> no_hits;
		if (no_hits == 0)
		{
			next_col++;
		}
		else if (no_hits == 1)
		{
			if (!unresolved_2_rows.empty())
			{
				int row = unresolved_2_rows.top();
				unresolved_2_rows.pop();
				solutions.push_back({ row,next_col++ });
			}
			else if (!unresolved_3_rows.empty())
			{
				int row = unresolved_3_rows.top();
				unresolved_3_rows.pop();
				solutions.push_back({ row,next_col });
				solutions.push_back({ next_row++,next_col++ });
			}
			else
			{
				solutions.push_back({ next_row++,next_col++ });
			}
		}
		else if (no_hits == 2)
		{
			unresolved_2_rows.push(next_row);
			solutions.push_back({ next_row++,next_col++ });
		}
		else
		{
			if (!unresolved_3_rows.empty())
			{
				int row = unresolved_3_rows.top();
				unresolved_3_rows.pop();
				solutions.push_back({ row,next_col });
			}
			unresolved_3_rows.push(next_row);
			solutions.push_back({ next_row++,next_col++ });
		}
	}
	bool correct = unresolved_2_rows.empty() && unresolved_3_rows.empty();
	/*for (const auto& sol_pair: solutions)
	{
		if (sol_pair.first > n || sol_pair.second > n)
		{
			correct = false;
			break;
		}
	}*/
	if (correct)
	{
		cout << solutions.size() << "\n";
		for (const auto& sol_pair : solutions)
		{
			cout << sol_pair.first << " " << sol_pair.second << "\n";
		}
	}
	else
	{
		cout << "-1\n";
	}
	return 0;
}