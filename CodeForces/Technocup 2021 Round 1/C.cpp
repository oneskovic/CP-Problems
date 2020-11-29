#include <iostream>
#include <algorithm>
#include <vector>
#include <limits.h>
#include <unordered_map>
using namespace std;
#define ll long long

struct fret
{
	ll value;
	size_t index;
};

int main()
{
	ios::sync_with_stdio(false);
	vector<ll> g_strings(6);
	for (size_t i = 0; i < 6; i++)
		cin >> g_strings[i];

	int n;
	cin >> n;
	vector<fret> possible_frets; possible_frets.reserve(6 * n);
	for (size_t i = 0; i < n; i++)
	{
		ll note; cin >> note;
		for (size_t j = 0; j < 6; j++)
		{
			possible_frets.push_back({ note - g_strings[j],i });
		}
	}
	sort(possible_frets.begin(), possible_frets.end(), [](const fret& lhs, const fret& rhs) {return lhs.value < rhs.value; });

	int l = 0, r = 0;
	unordered_map<size_t,int> seen_indices;
	seen_indices[possible_frets[r].index]++;
	int unique_indices = 1;
	ll min_diff = LLONG_MAX;
	while (r < possible_frets.size() - 1)
	{
		if (unique_indices == n)
		{
			ll diff = possible_frets[r].value - possible_frets[l].value;
			min_diff = min(diff, min_diff);
			seen_indices[possible_frets[l].index]--;
			if (seen_indices[possible_frets[l].index] == 0)
				unique_indices--;
			l++;
		}
		while (unique_indices < n && r < possible_frets.size()-1)
		{
			r++;
			seen_indices[possible_frets[r].index]++;
			if (seen_indices[possible_frets[r].index] == 1)
				unique_indices++;
		}
	}
	cout << min_diff << "\n";
	return 0;
}
