#include <algorithm>
#include <iostream>
#include <vector>
#include <string>

using namespace std;
typedef long long ll;

ll gcd(ll a, ll b)
{
	if (b == 0)
		return a;
	return gcd(b, a % b);
}


ll solve(const vector<ll>& v)
{
	int n = v.size();
	ll gcd_even = v[0];
	ll gcd_odd = v[1];
	for (int i = 2; i < n; i++)
	{
		if (i % 2 == 0)
			gcd_even = gcd(gcd_even, v[i]);
		else
			gcd_odd = gcd(gcd_odd, v[i]);
	}


	for (int i = 0; i < n; i++)
	{
		if (i % 2 == 0)
		{
			if(gcd_odd > 0 && v[i] % gcd_odd == 0)
				gcd_odd = 0;
		}
		else
		{
			if (gcd_even > 0 && v[i] % gcd_even == 0)
				gcd_even = 0;
		}
	}
	return max(gcd_even, gcd_odd);
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int test_cnt; cin >> test_cnt;
	while (test_cnt--)
	{
		int n; cin >> n;
		vector<ll> v(n);
		for (int i = 0; i < n; i++)
			cin >> v[i];
		auto s = solve(v);
		cout << s << "\n";
		
	}
	return 0;
}
