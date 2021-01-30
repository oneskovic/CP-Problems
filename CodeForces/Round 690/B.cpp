#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

bool check(const string& s, int l, int r)
{
	string result = "";
	for (size_t i = 0; i < l; i++)
	{
		result += s[i];
	}
	for (size_t i = s.size()-r; i < s.size(); i++)
	{
		result += s[i];
	}
	return result == "2020";
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	int test_count; cin >> test_count;
	for (size_t test_no = 0; test_no < test_count; test_no++)
	{
		int n; cin >> n;
		string s; cin >> s;
		bool possible = false;
		for (size_t i = 0; i <= 4; i++)
		{
			for (size_t j = 4-i; j <= 4; j++)
			{
				if (check(s,i,j))
				{
					possible = true;
				}
			}
		}
		if (possible)
			cout << "YES\n";
		else
			cout << "NO\n";
	}
	return 0;
}