#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
using namespace std;
typedef long long ll;

ll bruteforce(ll x)
{
	vector<ll> possible_numbers;
	ll right = 0;
	ll right_pow_10 = 1;
	while (x >= 10)
	{
		ll digit1 = x % 10;
		x /= 10;
		ll digit2 = x % 10;
		x /= 10;

		ll new_number = 0;
		if (digit1+digit2 >= 10)
		{
			new_number = (x * 100 + (digit1 + digit2)) * right_pow_10 + right;

		}
		else
		{
			new_number = (x * 10 + (digit1 + digit2)) * right_pow_10 + right;
		}
		
		right = right_pow_10*digit1 + right;
		x *= 10;
		x += digit2;
		right_pow_10 *= 10;
		possible_numbers.push_back(new_number);
	}
	return *max_element(possible_numbers.begin(), possible_numbers.end());
}

string solve(const string& s)
{
	int rightmost_overflow = -1;
	for (int i = 0; i < s.size() - 1; i++)
	{
		int digit = s[i] - '0';
		int next_digit = s[i + 1] - '0';
		if (digit + next_digit >= 10)
		{
			rightmost_overflow = i;
		}
	}
	int leftmost_increase = -1;
	for (int i = 0; i < s.size() - 1; i++)
	{
		int digit = s[i] - '0';
		int next_digit = s[i + 1] - '0';
		if (digit + next_digit > digit)
		{
			leftmost_increase = i;
			break;
		}
	}

	string solution = "";
	if (rightmost_overflow != -1)
	{
		for (int i = 0; i < s.size(); i++)
		{
			if (i == rightmost_overflow)
			{
				int digit = s[i] - '0';
				int next_digit = s[i + 1] - '0';
				solution += to_string(digit + next_digit);
				i++;
			}
			else
			{
				solution += s[i];
			}
		}
	}
	else if (leftmost_increase != -1)
	{
		for (int i = 0; i < s.size(); i++)
		{
			if (i == leftmost_increase)
			{
				int digit = s[i] - '0';
				int next_digit = s[i + 1] - '0';
				solution += to_string(digit + next_digit);
				i++;
			}
			else
			{
				solution += s[i];
			}
		}
	}
	else
	{
		solution += s[0];
		for (int i = 2; i < s.size(); i++)
		{
			solution += s[i];
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
		string s; cin >> s;
		cout << solve(s) << "\n";

	}

	return 0;
}