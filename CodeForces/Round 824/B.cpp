#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>
using namespace std;
typedef long long ll;

ll find_max_k(ll val, ll x, const vector<ll>& possible_k_values)
{
	ll ub = val / (2 * x - 1);
	int n = possible_k_values.size();
	auto it = lower_bound(possible_k_values.begin()+n-ub-1, possible_k_values.end(), 1, [x, val](ll k, ll b) {
		ll r = val - (2 * x - 1) * k;
		int ok = (r >= x);
		return ok < b;
	});

	return *it;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int test_cnt; cin >> test_cnt;
	vector<ll> possible_k_values(1e7 + 2);
	iota(possible_k_values.begin(), possible_k_values.end(), 0);
	reverse(possible_k_values.begin(), possible_k_values.end());
	while (test_cnt--)
	{
		int n; cin >> n;
		ll x; cin >> x;
		ll sol = 0;
		for (int i = 0; i < n-1; i++)
		{
			ll val; cin >> val;
			ll k = find_max_k(val, x, possible_k_values);
			sol += k;
			ll rem = val - (2 * x - 1) * k;
			if (rem >= 2*x)
				sol++;
		}
		cout << sol << "\n";
	}

	return 0;
}