#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <set>
using namespace std;
typedef long long ll;

void generate(const string& s, int i, ll current_number, ll x, set<ll>& sol)
{
	if (i >= s.size())
	{
		if (current_number > 0)
			sol.insert(current_number);
		return;
	}
	
	int digit = s[i] - '0';
	generate(s, i + 1, current_number, x, sol);
	generate(s, i + 1, current_number * 10 + digit, x, sol);
}

ll bruteforce(string s, ll x)
{

	set<ll> numbers;
	generate(s, 0, 0, x, numbers);
	ll sol = 0;
	for (ll num : numbers)
		if (num % x == 0)
			sol++;	
	return sol;
}

vector<vector<int>> fill_dp(string s, ll x)
{
	string current_str = "";
	vector<vector<int>> dp(s.size(), vector<int>(x));
	vector<int> sums = vector<int>(x);
	for (int i = 0; i < s.size(); i++)
	{
		current_str += s[i];
		set<ll> numbers;
		generate(current_str, 0, 0, x, numbers);
		for (int num: numbers)
		{
			dp[i][num % x]++;
		}
		for (int j = 0; j < x; j++)
		{
			int temp = dp[i][j];
			dp[i][j] -= sums[j];
			sums[j] = temp;
		}
	}
	return dp;
}

void print_dp(const vector<vector<int>>& dp)
{
	for (int i = 0; i < dp.size(); i++)
	{
		for (int j = 0; j < dp[0].size(); j++)
		{
			cout << setfill('0') << setw(2) << dp[i][j] << " ";
		}
		cout << "\n";
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	
	const ll mod = 1e9 + 7;

	string s; cin >> s;
	ll x; cin >> x;
	auto correct_dp = fill_dp(s, x);
	print_dp(correct_dp);

	vector<vector<int>> dp(s.size(), vector<int>(x));
	vector<int> prev_digit_pos(10, -1);
	dp[0][(s[0] - '0')%x] = 1;
	prev_digit_pos[s[0] - '0'] = 0;
	auto pref_sum = dp;
	for (int pos = 1; pos < s.size(); pos++)
	{
		int digit = s[pos] - '0';
		vector<int> sums;
		if (prev_digit_pos[digit] <= 0)
			sums = pref_sum[pos - 1];
		else
		{
			sums = pref_sum[pos - 1];
			vector<int> l = pref_sum[prev_digit_pos[digit] - 1];
			for (int i = 0; i < sums.size(); i++)
				sums[i] -= l[i];
		}
		for (int r = 0; r < x; r++)
		{
			int new_rem = r * 10 + digit;
			new_rem %= x;
			dp[pos][new_rem] += sums[r];
		}
		if (digit > 0)
		{
			dp[pos][digit % x]++;
		}

		pref_sum[pos] = pref_sum[pos - 1];
		for (int i = 0; i < sums.size(); i++)
		{
			pref_sum[pos][i] += dp[pos][i];
			pref_sum[pos][i] = (pref_sum[pos][i] + mod)%mod;
		}
		prev_digit_pos[digit] = pos;
	}
	cout << "\n";
	print_dp(dp);
	ll sol = 0;
	for (int pos: prev_digit_pos)
	{
		if (pos != -1)
		{
			sol += dp[pos][0];
			sol %= mod;
		}
	}
	cout << sol << "\n";

	return 0;
}