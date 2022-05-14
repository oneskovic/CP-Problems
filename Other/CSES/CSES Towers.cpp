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
	int n; cin >> n;
	vector<ll> elements(n);
	for (int i = 0; i < n; i++)
		cin >> elements[i];
	
	multiset<ll> towers;
	for (int i = 0; i < n; i++)
	{
		auto ub = towers.upper_bound(elements[i]);
		if (ub == towers.end())
		{
			towers.insert(elements[i]);
		}
		else
		{
			towers.erase(ub);
			towers.insert(elements[i]);
		}
	}
	cout << towers.size() << "\n";
	return 0;
}