#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <random>
#include <chrono>
using namespace std;
typedef long long ll;

int char_to_digit(char c)
{
	return c - '0';
}

ll brutus(const string& s)
{
	int n = s.size();
	ll sol = 0;
	for (int i = 0; i < n-2; i++)
	{
		for (int j = i+1; j < n-1; j++)
		{
			int mod_first = (i == 0 ? char_to_digit(s[0]) : 10 * char_to_digit(s[i - 1]) + char_to_digit(s[i]));
			mod_first %= 4;
			int mod_mid = (j == i + 1 ? char_to_digit(s[j]) : 10 * char_to_digit(s[j - 1]) + char_to_digit(s[j]));
			mod_mid %= 4;
			int mod_last = (j == n - 2 ? char_to_digit(s[n - 1]) : 10 * char_to_digit(s[n - 2]) + char_to_digit(s[n - 1]));
			mod_last %= 4;
			if ((mod_first + mod_mid + mod_last)%4 == 0)
			{
				sol++;
			}
		}
	}
	return sol;
}

ll solve1(int end_size, int end_mod, const string& s)
{
	int n = s.size();
	vector<vector<int>> dp(n - end_size, vector<int>(4));
	for (size_t i = 1; i < n - end_size; i++)
	{
		int current_number = 10 * char_to_digit(s[i - 1]) + char_to_digit(s[i]);
		for (int j = 0; j < 4; j++)
		{
			dp[i][j] = dp[i - 1][j];
		}
		dp[i][current_number % 4]++;
	}

	ll solution = 0;
	for (int i = 0; i < n - end_size - 1; i++)
	{
		int current_number = char_to_digit(s[i]);
		if (i > 0)
		{
			current_number = 10 * char_to_digit(s[i - 1]) + char_to_digit(s[i]);
		}
		int middle_mod = 4 - (current_number % 4 + end_mod) % 4;
		middle_mod %= 4;
		if (char_to_digit(s[i + 1]) % 4 == middle_mod)
		{
			solution++;
		}
		middle_mod %= 4;
		if (i < n - end_size - 2)
		{
			solution += dp[n - end_size - 1][middle_mod] - dp[i+1][middle_mod];
		}
	}
	return solution;
}

ll solve(const string& s)
{
	int n = s.size();
	if (n == 3)
	{
		if ((char_to_digit(s[0]) + char_to_digit(s[1]) + char_to_digit(s[2])) % 4 == 0)
		{
			return 1;
		}
		else
			return 0;
	}

	// Take [n-2][n-1]
	int mod_of_last = (10 * char_to_digit(s[n - 2]) + char_to_digit(s[n - 1])) % 4;
	ll sol = solve1(2, mod_of_last, s);

	// Take [n-1]
	mod_of_last = char_to_digit(s[n - 1]) % 4;
	int mod_of_mid = (10 * char_to_digit(s[n - 3]) + char_to_digit(s[n - 2])) % 4;
	int needed_mod_of_first = 4 - (mod_of_mid + mod_of_last) % 4;
	needed_mod_of_first %= 4;

	int mod_of_first = char_to_digit(s[0]) % 4;
	if (mod_of_first == needed_mod_of_first)
	{
		sol++;
	}
	for (int i = 1; i < n - 3; i++)
	{
		int current_number = 10 * char_to_digit(s[i - 1]) + char_to_digit(s[i]);
		mod_of_first = current_number % 4;
		if (mod_of_first == needed_mod_of_first)
		{
			sol++;
		}
	}

	mod_of_mid = char_to_digit(s[n - 2]) % 4;
	mod_of_first = (10 * char_to_digit(s[n - 4]) + char_to_digit(s[n - 3])) % 4;
	if ((mod_of_last + mod_of_mid + mod_of_first) % 4 == 0)
	{
		sol++;
	}

	return sol;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n; cin >> n;
	string s; cin >> s;
	cout << solve(s);
	/*int test_cnt = 1000000;
	int max_n = 5;
	srand(time(0));
	for (int t = 0; t < test_cnt; t++)
	{
		int n = rand() % (max_n) + 3;
		string s(n, ' ');
		for (int i = 0; i < n; i++)
		{
			if (i == 0)
			{
				s[i] = rand() % 9 + 1 + '0';
			}
			else
				s[i] = rand() % 10 + '0';
		}
		ll s1 = brutus(s);
		ll s2 = solve(s);
		if (s1 != s2)
		{
			cout << s << "\n";
			solve(s);
			cout << "WA\n";

		}
		else
			cout << "OK\n";
	}*/
}