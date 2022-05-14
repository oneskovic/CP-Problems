#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;
typedef long long ll;

ll count_matches(const string& s, const map<string, int>& cnt_str)
{
	vector<char> characters = { 'a','b','c','d','e','f','g','h','i','j','k' };
	ll solution = 0;
	for (int pos_to_fix : {0,1})
	{
		for (char c : characters)
		{
			if (s[pos_to_fix] != c)
			{
				string replaced_str = s;
				replaced_str[pos_to_fix] = c;
				if (cnt_str.find(replaced_str) != cnt_str.end())
				{
					solution += (ll)cnt_str.at(s) * cnt_str.at(replaced_str);
				}
			}
		}
	}
	return solution;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int test_cnt; cin >> test_cnt;
	while (test_cnt--)
	{
		int n; cin >> n;
		map<string, int> cnt_str;
		for (int i = 0; i < n; i++)
		{
			string s; cin >> s;
			cnt_str[s]++;
		}
		ll solution = 0;
		for (auto kvp: cnt_str)
		{
			solution += count_matches(kvp.first, cnt_str);
		}
		cout << solution/2 << "\n";
	}

	return 0;
}
