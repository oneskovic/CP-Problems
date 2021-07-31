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
		string s; cin >> s;
		int cnt_a = 0;
		int a_pos = -1;
		for (int i = 0; i < s.size(); i++)
		{
			if (s[i] == 'a')
			{
				a_pos = i;
				cnt_a++;
			}
		}
		if (cnt_a != 1)
		{
			cout << "NO\n";
			continue;
		}

		int l = a_pos-1, r = a_pos+1;
		char next_chr = 'b';
		bool valid = true;
		while (l >= 0 || r < s.size() && next_chr <= 'z')
		{
			if (l >= 0 && s[l] == next_chr)
			{
				next_chr++;
				l--;
			}
			else if (r < s.size() && s[r] == next_chr)
			{
				next_chr++;
				r++;
			}
			else
			{
				valid = false;
				break;
			}
		}
		if (valid && l < 0 && r == s.size())
		{
			cout << "YES\n";
		}
		else
			cout << "NO\n";
	}
	return 0;
}