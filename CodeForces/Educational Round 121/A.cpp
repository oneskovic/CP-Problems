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
		vector<int> letter_cnt(30);
		string s; cin >> s;
		for (int i = 0; i < s.size(); i++)
		{
			letter_cnt[s[i] - 'a']++;
		}
		for (int i = 0; i < 30; i++)
		{
			if (letter_cnt[i] == 2)
			{
				char c = 'a' + i;
				cout << c << c;
			}
		}
		for (int i = 0; i < 30; i++)
		{
			if (letter_cnt[i] == 1)
			{
				char c = 'a' + i;
				cout << c;
			}
		}
		cout << "\n";
	}

	return 0;
}