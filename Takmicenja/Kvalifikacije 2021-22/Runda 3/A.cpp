#include <algorithm>
#include <iostream>
#include <vector>
#include <set>
using namespace std;
typedef long long ll;


int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	ll n, k; cin >> n >> k;
	vector<ll> species(n);
	for (ll i = 0; i < n; i++)
	{
		cin >> species[i];
	}

	set<ll> ancestors;
	for (ll i = 0; i < n; i++)
	{
		ll ancestor = species[i] / k;
		ancestors.insert(ancestor);
	}
	cout << ancestors.size() << "\n";

	return 0;
}