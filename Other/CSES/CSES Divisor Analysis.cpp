#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;
const ll mod = 1e9 + 7;

ll binpow(ll number, ll degree, ll mod = 1e9+7)
{
	if (degree == 0)
		return 1;
	ll res = binpow(number, degree / 2);
	res = (res * res) % mod;
	if (degree % 2 == 1)
	{
		res *= number;
		res %= mod;
	}
	return res;
}

ll get_product_of_divisors(const vector<pair<ll, ll>>& prime_cnt)
{
	int n = prime_cnt.size();
	vector<ll> prefix_product(n);
	vector<ll> suffix_product(n);
	prefix_product[0] = prime_cnt[0].second + 1;
	suffix_product[n - 1] = prime_cnt[n - 1].second + 1;
	for (int i = 1; i < n; i++)
	{
		prefix_product[i] = prefix_product[i - 1] * (prime_cnt[i].second + 1);
		prefix_product[i] %= (mod-1);
	}
	for (int i = n-2; i >= 0; i--)
	{
		suffix_product[i] = suffix_product[i + 1] * (prime_cnt[i].second + 1);
		suffix_product[i] %= (mod - 1);
	}


	vector<ll> counts(n);
	for (int i = 0; i < n; i++)
	{
		ll product_all = 1;
		if (i > 0)
		{
			product_all *= prefix_product[i - 1];
		}
		if (i < n-1)
		{
			product_all *= suffix_product[i + 1];
		}
		product_all %= (mod - 1);
		counts[i] = product_all;
		ll degree = prime_cnt[i].second;
		ll temp = degree * (degree + 1) / 2;
		temp %= (mod - 1);
		counts[i] *= temp;
		counts[i] %= (mod-1);
	}
	ll result = 1;
	for (int i = 0; i < n; i++)
	{
		result *= binpow(prime_cnt[i].first, counts[i]);
		result %= mod;
	}
	return result;
}

ll get_divisor_count(const vector<pair<ll,ll>>& prime_cnt)
{
	int n = prime_cnt.size();
	vector<ll> degrees(n);
	ll product_all = 1;
	for (int i = 0; i < n; i++)
	{
		degrees[i] = prime_cnt[i].second;
		product_all *= (degrees[i] + 1);
		product_all %= mod;
	}
	return product_all;
}

ll get_divisor_sum(const vector<pair<ll, ll>>& prime_cnt)
{
	int n = prime_cnt.size();
	ll solution = 1;
	for (int i = 0; i < n; i++)
	{
		ll p = prime_cnt[i].first;
		ll deg = prime_cnt[i].second;
		ll mod_inv = binpow(p - 1, mod - 2);
		ll sum = binpow(p, deg + 1) - 1;
		sum *= mod_inv;
		sum %= mod;
		solution *= sum;
		solution %= mod;
	}
	return solution;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n; cin >> n;
	vector<pair<ll, ll>> prime_cnt(n);
	for (int i = 0; i < n; i++)
	{
		cin >> prime_cnt[i].first >> prime_cnt[i].second;
	}


	cout << get_divisor_count(prime_cnt) << endl;
	cout << get_divisor_sum(prime_cnt) << endl;
	cout << get_product_of_divisors(prime_cnt) << endl;


	return 0;
}