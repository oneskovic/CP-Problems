#include <algorithm>
#include <iostream>
#include <vector>
#include <chrono>

using namespace std;
typedef long long ll;
const ll mod = 1e9 + 7;

long long binpow(ll a, ll b) {
	ll res = 1;
	while (b > 0) {
		if (b & 1)
			res = (res * a) % mod;
		a = (a * a) % mod;
		b >>= 1;
	}
	return res;
}

vector<ll> precomputed_factorial(2 * 1e5 + 10);
ll modular_inverse(ll x)
{
	return binpow(x, mod - 2);
}

ll n_choose_k(ll n, ll k)
{
	ll n_fact = precomputed_factorial[n];
	ll k_fact = precomputed_factorial[k];
	ll n_minus_k_fact = precomputed_factorial[n - k];
	ll solution = n_fact * modular_inverse(k_fact);
	solution %= mod;
	return (solution * modular_inverse(n_minus_k_fact)) % mod;
}

ll solve(ll n, ll k)
{
	if (n == 1)
	{
		return binpow(2, k);
	}

	ll count_equal_for_col = 0;
	for (int i = 0; i < n; i += 2)
	{
		count_equal_for_col += n_choose_k(n, i);
		count_equal_for_col %= mod;
	}

	if (n % 2 == 1)
	{
		count_equal_for_col++;
		return binpow(count_equal_for_col, k);
	}
	else
	{
		ll solution = 0;
		for (int i = 0; i < k; i++)
		{
			ll any_result = binpow(2, n * i);
			ll equal_result = binpow(count_equal_for_col, k - i - 1);
			solution += (any_result * equal_result) % mod;
		}
		solution += binpow(count_equal_for_col, k);
		return solution % mod;
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int test_cnt; cin >> test_cnt;

	precomputed_factorial[0] = 1;
	for (ll i = 1; i < precomputed_factorial.size(); i++)
		precomputed_factorial[i] = (precomputed_factorial[i - 1] * i) % mod;

	while (test_cnt--)
	{
		ll n, k; cin >> n >> k;
		cout << solve(n, k) % mod << "\n";
	}
	return 0;
}