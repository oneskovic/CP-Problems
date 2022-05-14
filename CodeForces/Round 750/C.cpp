#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
using namespace std;
typedef long long ll;

ll solve_given_skippable(const string& s, char skippable_chr)
{
	int n = s.size();
	int l = 0, r = n-1;
	ll skip_count = 0;
	while (l >= 0 && l < r)
	{
		if (s[l] == s[r])
		{
			l++; r--;
		}
		else if (s[l] == skippable_chr)
		{
			skip_count++;
			l++;
		}
		else if(s[r] == skippable_chr)
		{
			skip_count++;
			r--;
		}
		else
		{
			return LLONG_MAX;
		}
	}
	return skip_count;
}

bool check_if_removing_gives_palindrome(const string& s, char chr_to_remove)
{
	int n = s.size();
	string new_s = ""; new_s.reserve(s.size());
	for (int i = 0; i < n; i++)
	{
		if (s[i] != chr_to_remove)
		{
			new_s += s[i];
		}
	}
	return new_s == string(new_s.rbegin(), new_s.rend());
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int test_cnt; cin >> test_cnt;
	while (test_cnt--)
	{
		int n; cin >> n;
		string s; cin >> s;
		string reversed_s = s; reverse(reversed_s.begin(), reversed_s.end());
		char c1 = 'Z', c2 = 'Z';
		for (int i = 0; i < n; i++)
		{
			if (s[i] != reversed_s[i])
			{
				c1 = s[i];
				c2 = reversed_s[i];
			}
		}
		if (c1 == 'Z')
		{
			cout << "0\n";
		}
		else
		{
			ll sol1 = solve_given_skippable(s, c1);
			ll sol2 = solve_given_skippable(s, c2);
			if (sol1 == sol2 && sol1 == LLONG_MAX)
			{
				cout << "-1\n";
			}
			else
			{
				cout << min(sol1, sol2) << "\n";
			}
		}
	}

	return 0;
}