#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;
#define ll long long

ll count_pairs(const string& s)
{
	ll count = 0;
	for (size_t i = 1; i < s.size(); i++)
	{
		if (s[i-1] == s[i])
		{
			count++;
		}
	}
	return count;
}

ll solve(const string& test)
{
	string test1 = string(test.size() + 2, '1');
	string test2 = string(test.size() + 2, '0');
	test1[0] = '0'; test2[0] = '1';
	for (size_t i = 1; i <= test.size(); i++)
	{
		test1[i] = test[i - 1];
		test2[i] = test[i - 1];
	}
	return min(count_pairs(test1), count_pairs(test2)) / 2;
}

int main()
{
	ios::sync_with_stdio(false);
	int test_count; cin >> test_count;
	for (size_t test_no = 0; test_no < test_count; test_no++)
	{
		int n; cin >> n;
		string s; cin >> s;
		cout << solve(s) << "\n";
	}
	return 0;
}