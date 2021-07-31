#include <algorithm>
#include <iostream>
#include <vector>
#include <chrono>
using namespace std;
typedef long long ll;

ll gcd(ll a, ll b)
{
	if (b == 0)
		return a;
	return gcd(b, a % b);
}

pair<ll,ll> check(ll a, ll b)
{
	if (a == b)
	{
		return { -1,-1 };
	}
	ll max_gcd = 0;
	int min_moves = -1;
	for (int i = 0; i < 1e5; i++)
	{
		ll g = gcd(a + i, b + i);
		if (g > max_gcd || (g == max_gcd && i < min_moves))
		{
			max_gcd = g;
			min_moves = i;
		}
	}
	for (int i = 0; i < 1e5; i++)
	{
		ll g = gcd(a - i, b - i);
		if (g > max_gcd || (g == max_gcd && i < min_moves))
		{
			max_gcd = g;
			min_moves = i;
		}
	}
	return { max_gcd,min_moves };
}

pair<ll,ll> solve(ll a, ll b)
{
	if (a > b)
		swap(a, b);
	// a <= b
	b -= a;
	if (b == 0)
	{
		cout << "0 0\n";
		return { -1,-1 };
	}
	else
	{
		ll g = b;
		ll moves_to_go_up = min(a % g, g - a%g);
		ll min_moves = min(a, moves_to_go_up);

		cout << b << " " << min_moves << "\n";
		return { b,min_moves };
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	srand(time(0));
	int test_cnt; cin >> test_cnt;
	while (test_cnt--)
	{
		ll a, b; cin >> a >> b;
		solve(a, b);
	}
	return 0;
}