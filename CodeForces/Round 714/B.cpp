#include <algorithm>
#include <iostream>
#include <vector>
#include <numeric>
#include <map>
using namespace std;
typedef long long ll;

ll mod = 1e9 + 7;
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

vector<ll> factorial;

ll mod_inv(ll n)
{
	ll x, y;
	gcd(n, mod, x, y);
	return (x % mod + mod) % mod;
}

ll n_choose_k (ll n, ll k)
{
	
	ll res = factorial[n] * mod_inv(factorial[n - k]);
	res %= mod;
	return (res * mod_inv(k)) % mod;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int test_count; cin >> test_count;
	for (int test_no = 0; test_no < test_count; test_no++)
	{
		int n;
		cin >> n;

		vector<ll> elements(n);
		vector<ll> count_zeros(64); // Number of numbers that have a zero at position i
		map<ll, ll> element_cnt;
		for (int i = 0; i < n; i++)
		{
			ll element; cin >> element;
			elements[i] = element;
			element_cnt[element]++;
			ll mask = 1;
			int pow2 = 0;
			while (mask < ((ll)1 << 62))
			{
				if (!(mask & element))
				{
					count_zeros[pow2]++;
				}
				pow2++;
				mask <<= 1;
			}
		}

		factorial = vector<ll>(n+1);
		factorial[0] = 1;
		for (int i = 1; i <= n; i++)
		{
			factorial[i] = i * factorial[i - 1];
			factorial[i] %= mod;
		}

		ll solution = 0;
		for (auto kvp: element_cnt)
		{
			if (kvp.second < 2)
				continue;

			ll combinations = 1;
			ll element = kvp.first;
			ll mask = 1;
			int pow2 = 0;
			while (mask < ((ll)1 << 62))
			{
				if (element & mask)
				{
					if (count_zeros[pow2] > 0)
					{
						combinations = 0;
						break;
					}
				}
				pow2++;
				mask <<= 1;
			}

			if (combinations == 1)
			{
				combinations = 2 * n_choose_k(kvp.second, 2);
				combinations %= mod;
				combinations *= factorial[n - 2];
				combinations %= mod;
			}
			solution += combinations;
			solution %= mod;
		}
		cout << solution << "\n";
	}
	return 0;
}