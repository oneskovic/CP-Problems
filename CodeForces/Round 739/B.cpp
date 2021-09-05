#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

typedef long long ll;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	int test_cnt; cin >> test_cnt;
	while (test_cnt--)
	{
		ll a, b, c;
		cin >> a >> b >> c;
		if (a > b)
			swap(a, b);

		ll start_a = a, start_b = b;

		b -= a;
		a = 0;
		if (b < 2)
		{
			cout << "-1\n";
		}
		else
		{
			ll node_cnt = 2 * b;
			if (c > node_cnt || start_a > node_cnt || start_b > node_cnt
			{
				cout << -1 << "\n";
			}
			else
			{
				if (c > b)
				{
					cout << c - b << "\n";
				}
				else
				{
					cout << c + b << "\n";
				}
			}
		}
	}

	return 0;
}