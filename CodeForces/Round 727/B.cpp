#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
using namespace std;
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n,q; cin >> n>>q;
	vector<vector<int>> letter_cnt(30,vector<int>(n));
	string s; cin >> s;
	letter_cnt[s[0] - 'a'][0] = 1;
	for (int i = 1; i < n; i++)
	{
		int current_letter = s[i] - 'a';
		for (int letter = 0; letter < 30; letter++)
		{
			if (letter == current_letter)
			{
				letter_cnt[letter][i] = letter_cnt[letter][i - 1] + 1;
			}
			else
			{
				letter_cnt[letter][i] = letter_cnt[letter][i - 1];
			}
		}
	}

	for (int i = 0; i < q; i++)
	{
		int l, r; cin >> l >> r;
		l--;
		r--;
		vector<int> substr_letters(30, 0);
		if (l == 0)
		{
			for (int letter = 0; letter < 30; letter++)
			{
				substr_letters[letter] = letter_cnt[letter][r];
			}
		}
		else
		{
			for (int letter = 0; letter < 30; letter++)
			{
				substr_letters[letter] = letter_cnt[letter][r] - letter_cnt[letter][l - 1];
			}
		}

		long long solution = 0;
		for (int letter = 0; letter < 30; letter++)
		{
			solution += substr_letters[letter] * (letter+1);
		}
		cout << solution << "\n";
	}

	
	return 0;
}