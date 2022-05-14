#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <chrono>
using namespace std;
typedef long long ll;
const ll mod = 998244353;

vector<ll> precomputed_factorial;

bool is_good(vector<pair<ll,int>> temp)
{
	vector<ll> v(temp.size());
	for (int i = 0; i < temp.size(); i++)
	{
		v[i] = temp[i].first;
	}
	vector<ll> time(v.size(), -2);
	ll t = 0;
	bool any_remaining = true;
	while (any_remaining)
	{
		any_remaining = false;
		for (int i = 0; i < v.size(); i++)
		{
			if (v[i] > 0)
			{
				any_remaining = 1;
				if (time[i] == t - 1)
				{
					return false;
				}
				v[i]--;
				time[i] = t;
				t++;
			}
		}
	}
	
	return true;
}

ll brutus(vector<ll> v)
{
	vector<pair<ll, int>> temp(v.size());
	for (int i = 0; i < v.size(); i++)
	{
		temp[i] = { v[i],i };
	}
	sort(temp.begin(), temp.end());
	int cnt_bad = 0;
	do
	{
		if (!is_good(temp))
		{
			cnt_bad++;
		}
	} while (next_permutation(temp.begin(), temp.end()));
	return precomputed_factorial[v.size()] - cnt_bad;
}

ll binpow(ll a, ll b) {
	a %= mod;
	ll res = 1;
	while (b > 0) {
		if (b % 2 == 1)
			res = res * a % mod;
		a = a * a % mod;
		b >>= 1;
	}
	return res;
}


ll mod_inv(ll x)
{
	return binpow(x, mod - 2);
}

ll n_choose_k(ll n, ll k)
{
	ll res = (precomputed_factorial[n] * mod_inv(precomputed_factorial[n - k])) % mod;
	res *= mod_inv(precomputed_factorial[k]) % mod;
	return res % mod;
}

ll solve(vector<ll>& v)
{
	ll n = v.size();
	sort(v.begin(), v.end());
	ll cnt_greatest = count(v.begin(), v.end(), v.back());
	ll cnt_one_less = count(v.begin(), v.end(), v.back() - 1);
	ll cnt_bad = n_choose_k(n, cnt_greatest + cnt_one_less);
	if (cnt_greatest > 1)
	{
		cnt_bad = 0;
	}
	cnt_bad *= precomputed_factorial[cnt_greatest];
	cnt_bad %= mod;
	cnt_bad *= precomputed_factorial[cnt_one_less];
	cnt_bad %= mod;
	cnt_bad *= precomputed_factorial[n - cnt_greatest - cnt_one_less];
	cnt_bad %= mod;
	ll solution = precomputed_factorial[n] - cnt_bad;
	solution += mod;
	solution %= mod;
	return solution;
}

void test()
{
	int n = rand() % 7 + 2;
	vector<ll> v(n);
	for (int i = 0; i < n; i++)
	{
		v[i] = rand() % 100 + 1;
	}
	ll res1 = solve(v);
	ll res2 = brutus(v);
	if (res1 != res2)
	{
		cout << "wa\n";
		brutus(v);
		solve(v);
	}
	else
		cout << "ok\n";
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	srand(time(0));
	int max_n = 2 * 1e5 + 2;
	precomputed_factorial = vector<ll>(max_n);
	precomputed_factorial[0] = 1;
	for (ll i = 1; i < max_n; i++)
		precomputed_factorial[i] = (precomputed_factorial[i - 1] * i)%mod;
	

	int test_cnt; cin >> test_cnt;
	while (test_cnt--)
	{
		int n; cin >> n;
		vector<ll> v(n);
		for (int i = 0; i < n; i++)
		{
			cin >> v[i];
		}
		cout << solve(v) << "\n";
		//test();
	}

	return 0;
}