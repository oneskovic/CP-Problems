#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <map>
using namespace std;
typedef long long ll;

ll gcd(ll a, ll b)
{
	if (b == 0)
		return a;
	return gcd(b, a % b);
}

struct point
{
	ll x, y;
};

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n; cin >> n;
	vector<point> points(n);
	for (int i = 0; i < n; i++)
		cin >> points[i].x >> points[i].y;
	
	map<tuple<ll, ll, ll>, ll> lines_cnt; // Tuple dy, dx, length^2
	for (int i = 0; i < n; i++)
	{
		for (int j = i+1; j < n; j++)
		{
			ll dy = points[i].y - points[j].y;
			ll dx = points[i].x - points[j].x;

			ll len = dy * dy + dx * dx;

			if (dy == 0)
			{
				dy = -1;
				dx = -2;
			}
			else if (dx == 0)
			{
				dx = -1;
				dy = -2;
			}
			else
			{
				ll g = gcd(dy, dx);
				dy /= g;
				dx /= g;
			}
			lines_cnt[tuple<ll, ll, ll>(dy, dx, len)]++;
		}
	}

	ll solution = 0;
	for (auto kvp: lines_cnt)
	{
		ll dy = get<0>(kvp.first);
		ll dx = get<1>(kvp.first);
		ll len = get<2>(kvp.first);
		ll cnt = kvp.second;

		ll longer_len = 4 * len;
		solution += cnt * lines_cnt[tuple<ll, ll, ll>(dy, dx, longer_len)];
	}
	cout << solution << "\n";
	return 0;
}