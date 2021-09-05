#include <algorithm>
#include <iostream>
#include <vector>
#include <set>
using namespace std;
typedef long long ll;

ll min_number_bruteforce(ll target, const vector<int>& digits, ll current_number, bool larger = false)
{
	if (current_number < target)
	{
		ll min_number = LLONG_MAX;
		for (int digit : digits)
		{
			if (digit == 0 && current_number == 0)
				continue;
			current_number *= 10;
			current_number += digit;
			min_number = min(min_number_bruteforce(target, digits, current_number), min_number);
			current_number /= 10;
		}
		return min_number;
	}
	else
	{
		return current_number;
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	int test_cnt; cin >> test_cnt;
	while (test_cnt--)
	{
		ll target_number; cin >> target_number;
		int k; cin >> k;
		ll solution = LLONG_MAX;
		for (int digit = 1; digit <= 9; digit++)
		{
			solution = min(solution, min_number_bruteforce(target_number, { digit }, 0));
		}
		if (k == 1)
		{	
			cout << solution << "\n";
		}
		else
		{
			set<int> all_digits;
			ll target_cpy = target_number;
			while (target_cpy > 0)
			{
				all_digits.insert(target_cpy % 10);
				target_cpy /= 10;
			}
			if (all_digits.size() > 1)
			{
				int digit1 = *all_digits.begin();
				int digit2 = *(++all_digits.begin());
				solution = min(solution, min_number_bruteforce(target_number, { digit1,digit2 }, 0));
			}
			cout << solution << "\n";
		}
	}

	return 0;
}