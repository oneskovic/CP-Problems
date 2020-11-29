#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <numeric>
using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	int test_count; cin >> test_count;
	for (size_t test_no = 0; test_no < test_count; test_no++)
	{
		int n; cin >> n;
		map<int, int> index_that_chose;
		for (int i = 1; i <= n; i++)
		{
			int chosen_number; cin >> chosen_number;
			if (index_that_chose[chosen_number] != 0)
				index_that_chose[chosen_number] = -1;
			else
				index_that_chose[chosen_number] = i;
		}

		bool winner_found = false;
		for (auto kvp: index_that_chose)
		{
			if (kvp.second != -1)
			{
				cout << kvp.second << "\n";
				winner_found = true;
				break;
			}
		}
		if (!winner_found)
			cout << "-1\n";
	}
	return 0;
}