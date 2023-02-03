#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;

const ll mod = 1e9 + 7;

vector<ll> factorial_upto(int n)
{
	vector<ll> fact(n + 1);
	fact[0] = 1;
	for (int i = 1; i <= n; i++)
		fact[i] = (fact[i - 1] * i)%mod;
	return fact;
}

ll binpow(ll x, ll power)
{
	if (power == 1)
		return x;
	
	ll res = binpow(x, power / 2);
	if (power % 2 == 0)
		return (res * res) % mod;
	
	else
		return ((res * res) % mod * x) % mod;
}

ll mod_inv(ll x)
{
	return binpow(x, mod - 2);
}

ll n_choose_k(int n, int k, const vector<ll>& fact)
{
	if (k > n)
		return 0;
	
	ll numerator = fact[n];
	ll denom = (fact[n - k] * fact[k]) % mod;
	return (numerator * mod_inv(denom)) % mod;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	auto fact = factorial_upto(1e5 + 2);
	int n, k; cin >> n >> k;
	ll res = 0;
	int cnt_mod = 0;
	for (int i = 0; i <= k; i++)
		res += n_choose_k(n, i, fact);
	
	cout << res % mod << "\n";
	

	return 0;
}
