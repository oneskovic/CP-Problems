#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>
#include <stack>
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

ll modular_inverse(ll number)
{
	ll inverse, temp;
	gcd(number, mod, inverse, temp);
	return inverse;
}

ll fact(int n)
{
	ll result = 1;
	for (ll i = 2; i <= n; i++)
	{
		result *= i;
		result %= mod;
	}
	return result;
}
ll n_choose_k(int n, int k)
{
	ll divisor = (fact(n - k) * fact(k))%mod;
	return (fact(n) * modular_inverse(divisor))%mod;
}

ll multiply_modulo(vector<ll> numbers)
{
	ll result = 1;
	for (size_t i = 0; i < numbers.size(); i++)
	{
		result *= numbers[i];
		result %= mod;
	}
	return result;
}

ll count_given_steps(int count_leq, int count_greater, int x, int n)
{
	int existing_greater = n - x, existing_leq = x-1;
	if (count_leq > existing_leq || count_greater > existing_greater)
		return 0;
	int remaining = n - 1 - count_greater - count_leq;

	ll total = multiply_modulo({
		n_choose_k(existing_greater, count_greater), fact(count_greater),
		n_choose_k(existing_leq, count_leq), fact(count_leq),
		fact(remaining) });
	
	return ((total%mod)+mod)%mod;
}

int main()
{
	int n, x, pos; cin >> n >> x >> pos;
	//cout << brutus(x, n, pos) << "\n";
	int end_l = pos, end_r = pos + 1;
	int left = 0, right = n;
	
	int count_leq = 0, count_greater = 0;
	while (left < right)
	{
		int mid = (left + right) / 2;
		if (mid <= end_l)
		{
			left = mid + 1;
			count_leq++;
		}
		else
		{
			right = mid;
			count_greater++;
		}
	}
	cout << count_given_steps(count_leq-1, count_greater, x, n);
	return 0;
}