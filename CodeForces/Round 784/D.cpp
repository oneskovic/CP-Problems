#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
using namespace std;
typedef long long ll;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int test_cnt; cin >> test_cnt;
	while (test_cnt--)
	{
		int n; cin >> n;
		string s; cin >> s;
		string current_str = "";
		bool possible = 1;
		for (int i = 0; i < n+1 && possible; i++)
		{
			if (i < n && s[i] != 'W')
			{
				current_str += s[i];
			}
			else
			{
				if (current_str.size() == 0)
					continue;
				if (current_str.size() < 2)
				{
					possible = false;
					break;
				}
				if (all_of(current_str.begin(), current_str.end(), [current_str](char c) { return c == current_str[0];}))
				{
					possible = false;
					break;
				}
				current_str = "";
			}
		}
		if (possible)
			cout << "yes\n";
		else
			cout << "no\n";
	}

	return 0;
}
