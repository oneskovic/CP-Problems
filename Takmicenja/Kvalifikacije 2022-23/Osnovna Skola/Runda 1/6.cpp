#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n; cin >> n;
	vector<int> v(n);
	vector<int> pref_even(n);
	vector<int> pref_odd(n);
	for (int i = 0; i < n; i++)
		cin >> v[i];
	if (v[0] % 2 == 0)
		pref_even[0] = 1;
	else
		pref_odd[0] = 1;

	for (int i = 1; i < n; i++)
	{
		pref_even[i] = pref_even[i - 1];
		pref_odd[i] = pref_odd[i - 1];
		if (v[i] % 2 == 0)
			pref_even[i]++;
		else
			pref_odd[i]++;
	}

	ll max_sol = 0;
	for (int i = 0; i < n; i++)
	{
		ll cnt_even_l = pref_even[i];
		ll cnt_odd_l = pref_odd[i];

		ll cnt_even_r = pref_even.back() - cnt_even_l;
		ll cnt_odd_r = pref_odd.back() - cnt_odd_l;
		
		ll sol = cnt_even_l * cnt_even_r + cnt_odd_l * cnt_odd_r;
		max_sol = max(max_sol, sol);
	}
	cout << max_sol << "\n";
	return 0;
}