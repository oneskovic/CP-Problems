#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;
#define ll long long

int main()
{
	ios::sync_with_stdio(false);
	int test_count; cin >> test_count;
	for (size_t test_no = 0; test_no < test_count; test_no++)
	{
		string s; cin >> s;
		if (s.size()%2 == 1)
		{
			cout << "NO\n";
			continue;
		}
		int position_open = -1, position_closed = -1;
		vector<int> counts(3);
		int count_pos = 0;
		for (size_t i = 0; i < s.size(); i++)
		{
			if (s[i] == '(')
			{
				position_open = i;
				count_pos++;
			}
			else if (s[i] == ')')
			{
				position_closed = i;
				count_pos++;
			}
			else
			{
				counts[count_pos]++;
			}
		}

		if (position_open < position_closed)
		{
			if ((counts[0]+counts[1]+counts[2]) % 2 == 0)
				cout << "YES\n";
			else
				cout << "NO\n";
		}
		else
		{
			if (counts[0] >= 1 && counts[2] >= 1 && (counts[0] + counts[1] + counts[2]) % 2 == 0)
				cout << "YES\n";
			else
				cout << "NO\n";
		}
	}
	return 0;
}