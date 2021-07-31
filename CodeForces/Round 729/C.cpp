#include <algorithm>
#include <limits.h>
#include <iostream>
#include <vector>

using namespace std;
typedef long long ll;
const ll mod = 1e9 + 7;

ll f(ll i)
{
	for (int j = 2; j <= 2*i; j++)
	{
		if (i % j > 0)
		{
			return j;
		}
	}
}

ll brutus(ll n)
{
	ll sum = 0;
	for (int i = 1; i <= n; i++)
	{
		cout << f(i) << " ";
		sum += f(i);
		sum %= mod;
	}
	cout << endl;
	return sum;
}

ll gcd(ll a, ll b)
{
	if (b == 0)
	{
		return a;
	}
	return gcd(b, a % b);
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	int test_cnt; cin >> test_cnt;
	while (test_cnt--)
	{
		ll n; cin >> n;
		//cout << brutus(n) << "\n";
		ll remaining = n;
		ll solution = 0;
		ll product = 1;
		ll current_number = 2;
		while (remaining > 0)
		{
			solution += current_number * remaining;
			solution %= mod;
			ll g = gcd(product, current_number);
			product /= g;
			product *= current_number;
			remaining = n / product;
			solution -= current_number * remaining;
			solution %= mod;
			current_number++;
		}
		solution = (solution + mod) % mod;
		cout << solution << "\n";
	}
	return 0;
}