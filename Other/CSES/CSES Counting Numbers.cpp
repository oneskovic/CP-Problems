#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
using namespace std;
typedef long long ll;

ll cnt_upto_n(ll end_number, const vector<vector<ll>>& dp)
{
	if (end_number <= 0)
		return 0;
	
	string end_number_str = to_string(end_number);
	int first_equal_pos = -1;
	for (int i = 1; i < end_number_str.size(); i++)
	{
		if (end_number_str[i] == end_number_str[i - 1])
		{
			first_equal_pos = i - 1;
			break;
		}
	}
	if (first_equal_pos != -1)
	{
		if (end_number_str[first_equal_pos] == '0')
			first_equal_pos-=2;
		
		end_number_str[first_equal_pos + 1]--;
		bool is_9 = true;
		for (int i = first_equal_pos + 2; i < end_number_str.size(); i++)
		{
			end_number_str[i] = is_9 ? '9' : '8';
			is_9 = !is_9;
		}
	}
	if (end_number_str[0] == '0')
		end_number_str.erase(end_number_str.begin());
	int max_len = end_number_str.size();
	
	ll cnt_to_end = 0;
	for (int i = 1; i < end_number_str[0] - '0'; i++)
		cnt_to_end += dp[i][max_len];
	
	for (int i = 1; i < end_number_str.size(); i++)
	{
		int prev_digit = end_number_str[i - 1] - '0';
		int current_digit = end_number_str[i] - '0';
		for (int j = 0; j < current_digit; j++)
			if (j != prev_digit)
				cnt_to_end += dp[j][max_len - i];
	}
	cnt_to_end++;
	for (int len = 1; len < max_len; len++)
		for (int i = 1; i <= 9; i++)
			cnt_to_end += dp[i][len];
	return cnt_to_end;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	ll l, r; cin >> l >> r;

	int max_len = to_string(r).size();
	vector<vector<ll>> dp(10, vector<ll>(max_len + 1));
	for (int i = 0; i <= 9; i++)
		dp[i][1] = 1;

	for (int len = 2; len <= max_len; len++)
		for (int i = 0; i <= 9; i++)
			for (int j = 0; j <= 9; j++)
				if (i != j)
					dp[i][len] += dp[j][len - 1];
	if (l == 0)
		cout << cnt_upto_n(r, dp) + 1;
	else
		cout << cnt_upto_n(r, dp) - cnt_upto_n(l - 1, dp) << "\n";
	return 0;
}