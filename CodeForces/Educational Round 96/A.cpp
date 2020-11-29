#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
	int t; cin >> t;
	for (size_t test_no = 0; test_no < t; test_no++)
	{
		int n; cin >> n;
		int no_threes = 0, no_fives = 0, no_sevens = 0;
		switch (n%3)
		{
		case 0:
			no_threes = n / 3;
			break;
		case 1:
			no_threes = n / 3;
			if (no_threes < 2)
			{
				cout << "-1\n";
				continue;
			}
			else
			{
				no_threes -= 2;
				no_sevens++;
			}
			break;
		case 2:
			no_threes = n / 3;
			if (no_threes < 1)
			{
				cout << "-1\n";
				continue;
			}
			else
			{
				no_threes--;
				no_fives++;
			}
			break;
		}
		cout << no_threes << " " << no_fives << " " << no_sevens << "\n";
	}
	return 0;
}