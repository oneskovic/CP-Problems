#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;
typedef long long ll;

int main()
{
	freopen("notlast.in", "r", stdin);
	freopen("notlast.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n; cin >> n;
	map<string, int> m = {
		{"Bessie",0},
		{"Elsie",0},
		{"Daisy",0},
		{"Gertie",0},
		{"Annabelle",0},
		{"Maggie",0},
		{"Henrietta",0}
	};

	for (int i = 0; i < n; i++)
	{
		string name; int amount;
		cin >> name >> amount;
		m[name] += amount;
	}
	vector<pair<int, string>> v; v.reserve(m.size());
	for (auto kvp: m)
		v.emplace_back(kvp.second, kvp.first);
	sort(v.begin(), v.end());
	int solution = -1;
	for (int i = 1; i < v.size(); i++)
	{
		if (v[i].first > v[0].first)
		{
			solution = i;
			break;
		}
	}
	if (solution == -1 || (solution < v.size()-1 && v[solution].first == v[solution+1].first))
		cout << "Tie\n";
	else
		cout << v[solution].second;

	return 0;
}