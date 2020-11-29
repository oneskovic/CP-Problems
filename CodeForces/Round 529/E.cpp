#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	int n; cin >> n;
	string brackets; cin >> brackets;
	vector<int> prefixes(n), minimums(n);
	int sum = 0;
	for (size_t i = 0; i < n; i++)
	{
		if (brackets[i] == '(')
			sum++;
		else
			sum--;

		prefixes[i] = sum;
	}
	int minimum = prefixes[n - 1];
	for (int i = n-1; i >= 0; i--)
	{
		minimum = min(minimum, prefixes[i]);
		minimums[i] = minimum;
	}

	if (abs(prefixes[n-1]) != 2)
		cout <<"0\n";
	else
	{
		char bracket_to_swap = prefixes[n - 1] == 2 ? '(' : ')';
		int delta = -prefixes[n - 1];
		int solution = 0;
		if (minimums[0] >= 0 || minimums[0] + delta >= 0)
		{
			for (size_t i = 0; i < n; i++)
			{
				if (brackets[i] == bracket_to_swap && minimums[i] + delta >= 0)
					solution++;
				if (prefixes[i] < 0)
					break;
			}
		}
		cout << solution << "\n";
	}
	return 0;
}