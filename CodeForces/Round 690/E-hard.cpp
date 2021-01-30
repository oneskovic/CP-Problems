#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
#define ll long long

const ll mod = 1e9 + 7;

vector<ll> factorial;

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
	return x;
}

ll n_choose_k(ll n, ll k)
{
	if (k > n)
		return 0;
	
	return factorial[n] * inverse(factorial[k] * factorial[n - k] % mod) % mod;
}

ll solve(int n, int m, int k, vector<ll> elements)
{
	sort(elements.begin(), elements.end());
	ll solution = 0;
	for (size_t i = 0; i <= max(0,n - m); i++)
	{
		ll current_element = elements[i];
		auto it = upper_bound(elements.begin(), elements.end(), current_element + k);
		ll element_count = it - (elements.begin() + i);

		solution += n_choose_k(element_count - 1, m - 1);
		solution %= mod;
	}
	return (solution + mod) % mod;
}

int main()
{
	factorial = vector<ll>(2e5 + 1);
	factorial[0] = 1;
	for (ll i = 1; i <= 2e5; i++)
		factorial[i] = (factorial[i - 1] * i) % mod;
	
	ios::sync_with_stdio(false);
	cin.tie(0);
	int test_count; cin >> test_count;
	for (size_t test_no = 0; test_no < test_count; test_no++)
	{
		int n, m, k;
		cin >> n >> m >> k;
		vector<ll> elements(n);
		for (size_t i = 0; i < n; i++)
			cin >> elements[i];
		
		cout << solve(n,m,k,elements) << "\n";
	}

	return 0;
}