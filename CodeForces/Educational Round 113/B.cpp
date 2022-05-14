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
		vector<string> games(n, string(n, ' '));
		vector<int> players_2;
		for (int i = 0; i < n; i++)
			if (s[i] == '2')
				players_2.push_back(i);
		if (players_2.size() > 0 && players_2.size() <= 2)
			cout << "NO\n";
		else
		{
			if (players_2.size() > 0)
			{
				for (int i = 1; i < players_2.size(); i++)
				{
					int player = players_2[i];
					int prev_player = players_2[i - 1];
					games[player][prev_player] = '+';
					games[prev_player][player] = '-';
				}
				games[players_2[0]][players_2.back()] = '+';
				games[players_2.back()][players_2[0]] = '-';
			}
			for (int i = 0; i < n; i++)
			{
				for (int j = 0; j < n; j++)
				{
					if (i == j)
						games[i][j] = 'X';
					else if (games[i][j] == ' ')
						games[i][j] = '=';
				}
			}
			cout << "YES\n";
			for (string s: games)
				cout << s << "\n";
		}
	}
	return 0;
}