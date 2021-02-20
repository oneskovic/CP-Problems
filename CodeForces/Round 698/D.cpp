#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
#define ll long long

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
	int test_count; cin >> test_count;
	for (size_t test_no	= 0; test_no < test_count; test_no++)
	{
		int n; cin >> n;
		ll k; cin >> k;
		vector<ll> elements(n);
		for (size_t i = 0; i < n; i++)
			cin >> elements[i];
		sort(elements.begin(), elements.end());
		for (size_t i = 1; i < n; i++)
			elements[i] -= elements[0];
		

		ll g = elements[1];
		for (size_t i = 2; i < n; i++)
		{
			g = gcd(g, elements[i]);
		}
		if ((k-elements[0]) % g == 0)
			cout << "YES\n";
		else
			cout << "NO\n";
	}
	return 0;
}