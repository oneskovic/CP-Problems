#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
#define ll long long
int main()
{
	int test_count; cin >> test_count;
	for (size_t test_no = 0; test_no < test_count; test_no++)
	{
		ll num_cols, available_blocks, jump_height;
		cin >> num_cols >> available_blocks >> jump_height;
		vector<int> column_heights(num_cols);
		for (size_t i = 0; i < num_cols; i++)
			cin>>column_heights[i];
		
		bool possible = true;
		for (size_t i = 0; i < num_cols-1 && possible; i++)
		{
			available_blocks += column_heights[i];
			if (jump_height < column_heights[i+1])
			{
				available_blocks -= (column_heights[i + 1] - jump_height);
			}
			if (available_blocks < 0)
				possible = false;
		}
		if (possible)
			cout << "YES\n";
		else
			cout << "NO\n";
	}
	return 0;
}