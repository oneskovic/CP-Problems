#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	ll n, m; cin >> n >> m;
	// x*(2*n-x) + y*(n-x) = m
	pair<ll, ll> sol = { -1,-1 };
	for (ll x = 1; m - x * (2 * n - x) >= 0 && x <= n; x++)
	{
		ll rem = m - x * (2 * n - x);
		if (rem % (n-x) == 0)
		{
			ll y = rem / (n - x);
			if (y > n-1)
			{
				continue;
			}
			sol = { x,y };
			break;
		}
	}
	if (sol.first == -1)
	{
		cout << "-1\n";
	}
	else
	{
		cout << sol.first + sol.second << "\n";
		for (int i = 0; i < sol.first; i++)
		{
			cout << i + 1 << " " << i + 1 << "\n";
		}
		for (int i = 0; i < sol.second; i++)
		{
			cout << 1 << " " << i + sol.first + 1 << "\n";
		}
	}

	return 0;
}