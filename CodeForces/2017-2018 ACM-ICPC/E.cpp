#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;

// 0 - empty
// 1 - pickup
// 2 - packman
bool check(vector<int> symbols, int k)
{
	int n = symbols.size();
	int leftmost_pickup = -1;
	for (int i = 0; i < n; i++)
	{
		if (symbols[i] == 1 && leftmost_pickup == -1)
		{
			leftmost_pickup = i;
		}
		else if (symbols[i] == 2)
		{
			int l = i - leftmost_pickup;
			if (leftmost_pickup != -1 && l > k)
			{
				return false;
			}
			int r = 0;
			if (leftmost_pickup == -1)
			{
				r = k;
			}
			else
			{
				if (3*l <= k)
				{
					r = k - 2 * l;
				}
				else
				{
					r = (k - l) / 2;
				}
			}
			int continue_from = i;
			if (i + r >= n)
				return 1;
			
			for (int j = 1; j <= r; j++)
			{
				if (symbols[i+j] == 2)
				{
					continue_from = i + j;
				}
				else if (symbols[i+j] == 1)
				{
					symbols[i + j] = 0;
				}
			}
			if (continue_from > i)
			{
				i = continue_from - 1;
			}
			leftmost_pickup = -1;
		}
	}
	if (leftmost_pickup != -1)
	{
		return false;
	}
	return true;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n; cin >> n;
	vector<int> symbols(n,2);
	string s; cin >> s;
	for (int i = 0; i < n; i++)
	{
		switch (s[i])
		{
		case '.':
			symbols[i] = 0;
			break;
		case '*':
			symbols[i] = 1;
			break;
		}
	}
	int l = 0, r = 3 * n;
	while (r - l > 1)
	{
		int mid = (l + r) / 2;
		if (check(symbols, mid))
			r = mid;
		else
			l = mid;
	}
	cout << r;

	return 0;
}