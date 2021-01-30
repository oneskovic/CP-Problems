#include <iostream>
#include <algorithm>
#include <vector>
#include <functional>
using namespace std;
#define ll long long
const ll mod = 1e9 + 7;

ll gcd(ll a, ll b, ll& x, ll& y) {
	if (b == 0) {
		x = 1;
		y = 0;
		return a;
	}
	ll x1, y1;
	ll d = gcd(b, a % b, x1, y1);
	x = y1;
	y = x1 - y1 * (a / b);
	return d;
}
ll inverse(ll n)
{
	ll x, y;
	gcd(n, mod, x, y);
	return (x % mod + mod) % mod;
}

ll factorial(ll n)
{
	ll fact = 1;
	for (ll i = 2; i <= n; i++)
	{
		fact *= i;
		fact %= mod;
	}
	return fact;
}

long long n_choose_k(int n, int k) {
	return (factorial(n) * inverse(factorial(k) * factorial(n-k))%mod);
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	int test_count; cin >> test_count;
	for (size_t test_no = 0; test_no < test_count; test_no++)
	{
		int n, tuple_size, max_diff; cin >> n; //>> tuple_size >> max_diff;

		tuple_size = 3; max_diff = 2;
		vector<ll> elements(n);
		for (size_t i = 0; i < n; i++)
			cin >> elements[i];
		sort(elements.begin(), elements.end());
		int r = n - 1;
		int l = r;
		ll result = 0;
		while (r >= 0)
		{
			while (l >= 0 && elements[r] - elements[l] <= 2)
			{
				l--;
				if (r-l+1 >= 3)
				{
					result += r - l - 1;
				}
			}
			r--;
		}
		cout << result << "\n";
	}
	return 0;
}