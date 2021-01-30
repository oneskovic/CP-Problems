#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;
#define ll long long

const ll mod = 1e9 + 7;
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	int test_count; cin >> test_count;
	for (size_t test_no = 0; test_no < test_count; test_no++)
	{
		int n; cin >> n;
		vector<ll> a(n);
		vector<ll> count_ones(64);

		for (size_t i = 0; i < n; i++)
		{
			ll new_element; cin >> new_element;
			ll mask = 1;
			for (size_t i = 0; i < 64; i++)
			{
				if (new_element & mask)
					count_ones[i]++;
				mask *= 2;
			}
			a[i] = new_element;
		}
		vector<ll> x(n);
		for (size_t i = 0; i < n; i++)
		{
			ll result = 0;
			ll mask = 1;
			for (size_t pos = 0; pos < 64; pos++)
			{
				if (a[i] & mask)
					result += (mask % mod) * n;
				else
					result += (mask % mod) * count_ones[pos];
				
				result %= mod;
				mask *= 2;
			}
			x[i] = result;
		}

		ll solution = 0;
		for (size_t i = 0; i < n; i++)
		{
			ll mask = 1;
			for (size_t pos = 0; pos < 64; pos++)
			{
				if (a[i] & mask)
					solution += (x[i] * (mask % mod)) % mod * count_ones[pos];
				solution %= mod;
				mask *= 2;
			}
		}
		cout << solution << "\n";
	}

	return 0;
}