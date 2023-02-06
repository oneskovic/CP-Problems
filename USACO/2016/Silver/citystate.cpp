#include <iostream>
#include <string>
#include <map>
using namespace std;
typedef long long ll;

int main()
{
	freopen("citystate.in", "r", stdin);
	freopen("citystate.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n; cin >> n;
	map<pair<string, string>, ll> m;
	for (int i = 0; i < n; i++)
	{
		string a, b; cin >> a >> b;
		string start_a(2, ' ');
		start_a[0] = a[0]; start_a[1] = a[1];
		pair<string, string> p = { start_a, b};
		m[p]++;
	}
	ll solution = 0;
	for (auto kvp: m)
	{
		auto key = kvp.first;
		ll count = kvp.second;
		if (key.first == key.second)
		{
			//solution += count * (count - 1) / 2;
		}
		else if (key.first < key.second)
		{
			auto reverse_p = key;
			swap(reverse_p.first, reverse_p.second);
			solution += count * m[reverse_p];
		}
	}
	cout << solution;

	return 0;
}