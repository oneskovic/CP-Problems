#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <set>
using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	int test_count; cin >> test_count;
	for (size_t test_no = 0; test_no < test_count; test_no++)
	{
		int sum; cin >> sum;
		string solution = "";
		set<int> available_digits = { 1,2,3,4,5,6,7,8,9 };

		for (int digit = 9; digit >= 1; digit--)
		{
			if (available_digits.find(digit) != available_digits.end() && digit <= sum)
			{
				solution += to_string(digit);
				sum -= digit;
				available_digits.erase(digit);
			}
		}
		if (sum == 0)
		{
			reverse(solution.begin(), solution.end());
			cout << solution << "\n";
		}
		else
		{
			cout << "-1\n";
		}
	}
	return 0;
}