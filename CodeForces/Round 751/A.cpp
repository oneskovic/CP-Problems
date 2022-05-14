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
		char min_chr = s[0];
		int min_pos = 0;
		for (int i = 0; i < s.size(); i++)
		{
			if (s[i] < min_chr)
			{
				min_pos = i;
				min_chr = s[i];
			}
		}
		cout << min_chr << " ";
		for (int i = 0; i < s.size(); i++)
		{
			if (i != min_pos)
			{
				cout << s[i];
			}
		}
		cout << "\n";
	}

	return 0;
}