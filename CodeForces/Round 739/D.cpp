#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
using namespace std;

typedef long long ll;

int count_ops(string n, string power)
{
	int ops = 0;
	int i = 0, j = 0;
	while (i < n.size() && j < power.size())
	{
		if (n[i] == power[j])
		{
			i++;
			j++;
		}
		else
		{
			i++;
			ops++;
		}
	}
	int remaining = n.size() - i + power.size() - j;
	return ops + remaining;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	int test_cnt; cin >> test_cnt;
	while (test_cnt--)
	{
		string n; cin >> n;
		int best_power = 0;
		int min_ops = INT_MAX;
		for (int power = 0; power <= 60; power++)
		{
			ll p = (ll)1 << power;
			int ops = count_ops(n, to_string(p));
			if (ops <= min_ops)
			{
				best_power = power;
				min_ops = ops;
			}
		}
		cout << min_ops << "\n";
	}

	return 0;
}