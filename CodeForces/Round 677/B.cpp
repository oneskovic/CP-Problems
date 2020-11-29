#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

int main()
{
	ios::sync_with_stdio(false);

	int test_count; cin >> test_count;
	for (size_t test_no = 0; test_no < test_count; test_no++)
	{
		int n; cin >> n;
		int first_one = -1, last_one = -1;
		int ones_count = 1;
		for (size_t i = 0; i < n; i++)
		{
			int element; cin >> element;
			if (element == 1)
			{
				if (first_one == -1)
				{
					first_one = i;
				}
				else
				{
					ones_count++;
					last_one = i;
				}
			}
		}
		if (last_one == -1)
		{
			cout << 0 << "\n";
		}
		else
		{
			cout << last_one - first_one + 1 - ones_count << "\n";
		}
	}
	return 0;
}