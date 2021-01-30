#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;
#define ll long long

ll gcd(ll a, ll b)
{
	if (b == 0)
		return a;
	return gcd(b, a % b);
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	int test_count; cin >> test_count;
	for (size_t test_no	= 0; test_no < test_count; test_no++)
	{
		int n; cin >> n;
		map<pair<ll, ll>, int> dx_dy_map;
		for (size_t i = 0; i < n; i++)
		{
			ll x1, y1, x2, y2;
			cin >> x1 >> y1 >> x2 >> y2;
			ll dx = x1 - x2;
			ll dy = y1 - y2;
			ll gcd_dx_dy = gcd(abs(dx), abs(dy));
			dx /= gcd_dx_dy;
			dy /= gcd_dx_dy;
			dx_dy_map[{ dx, dy }]++;
		}

		ll solution = 0;
		for (auto& kvp : dx_dy_map)
		{
			ll dx = kvp.first.first;
			ll dy = kvp.first.second;
			ll count = kvp.second;
			if (dx_dy_map.find({ -dx,-dy }) != dx_dy_map.end())
				solution += count * dx_dy_map[{-dx, -dy}];
			kvp.second = 0; // Avoid duplicate counting
		}
		cout << solution << "\n";
	}

	return 0;
}