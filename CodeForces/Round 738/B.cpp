#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <chrono>
using namespace std;
typedef long long ll;

int count_bad(const string& s)
{
	int cnt = 0;
	for (int i = 0; i < s.size()-1; i++)
	{
		if (s[i] == s[i+1])
		{
			cnt++;
		}
	}
	return cnt;
}

int brutus_recurse(string& s, int pos)
{
	if (pos == s.size())
	{
		return count_bad(s);
	}
	if (s[pos] == '?')
	{
		s[pos] = 'R';
		int s1 = brutus_recurse(s, pos + 1);
		s[pos] = 'B';
		int s2 = brutus_recurse(s, pos + 1);
		return min(s1, s2);
	}
	else
	{
		return brutus_recurse(s, pos + 1);
	}
}

int brutus(string s)
{
	return brutus_recurse(s, 0);
}

string rand_str(int n)
{
	string s(n, '?');
	for (int i = 0; i < n; i++)
	{
		int num = rand() % 3;
		if (num == 1)
		{
			s[i] = 'R';
		}
		else if (num == 2)
		{
			s[i] = 'B';
		}
	}
	return s;
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

		if (s[0] == '?')
		{
			int len_empty = 1;
			for (int i = 1; i < n; i++)
			{
				if (s[i] != '?')
					break;
				else
					len_empty++;
			}
			if (len_empty == n)
			{
				s[0] = 'R';
			}
			else
			{
				char end_char = 'R';
				if (s[len_empty] == 'R')
					end_char = 'B';
				if (len_empty % 2 == 1)
				{
					s[0] = end_char;
				}
				else
				{
					s[0] = (end_char == 'R' ? 'B' : 'R');
				}
			}
		}
		for (int i = 1; i < s.size(); i++)
		{
			if (s[i] == '?')
			{
				if (s[i - 1] == 'R')
					s[i] = 'B';
				else
					s[i] = 'R';
			}
		}
		cout << s << "\n";
	}
	return 0;
}