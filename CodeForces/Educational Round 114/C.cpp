#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;

ll brute_force(const vector<ll>& heros, ll heros_sum, ll dragon_def, ll dragon_attack)
{
	ll solution = LLONG_MAX;
	for (int j = 0; j < heros.size(); j++)
	{
		ll to_add = max(dragon_def - heros[j], (ll)0);
		to_add += max(dragon_attack - (heros_sum - heros[j]), (ll)0);
		solution = min(to_add, solution);
	}
	return solution;
}

ll solve(const vector<ll>& heros, ll dragon_def, ll x)
{
	ll solution = LLONG_MAX;
	auto it = lower_bound(heros.begin(), heros.end(), dragon_def);
	if (it == heros.end())
		it--;
	if (*it > dragon_def && it == heros.begin())
	{

	}
	else {
		if (*it > dragon_def)
		{
			it--;
		}
		if (*it >= -x)
		{
			solution = min(solution, dragon_def + x);
		}
	}

	it = lower_bound(heros.begin(), heros.end(), min(dragon_def, -x));
	if (it == heros.end())
		it--;
	if (*it > min(dragon_def, -x) && it == heros.begin())
	{

	}
	else {
		if (*it > min(dragon_def, -x))
			it--;
		solution = min(solution, dragon_def - *it);
	}

	it = lower_bound(heros.begin(),heros.end(), max(dragon_def, -x));
	if (it != heros.end())
	{
		ll sol1 = *it + x;
		ll sol2 = heros.back() + x;
		solution = min(solution,min(sol1, sol2));
	}
	it = lower_bound(heros.begin(), heros.end(), dragon_def);
	if (it != heros.end())
	{
		if (*it <= -x)
		{
			solution = min(solution, (ll)0);
		}
	}
	return solution;

	return 0;
}


int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n; cin >> n;
	vector<ll> heros(n);
	ll heros_sum = 0;
	for (int i = 0; i < n; i++)
	{
		cin >> heros[i];
		heros_sum += heros[i];
	}
	sort(heros.begin(), heros.end());
	int m; cin >> m;
	for (int i = 0; i < m; i++)
	{
		ll dragon_def, dragon_attack;
		cin >> dragon_def >> dragon_attack;
			
		//ll sol1 = brute_force(heros, heros_sum, dragon_def, dragon_attack);
		ll sol2 = solve(heros, dragon_def, dragon_attack - heros_sum);
		cout << sol2 << "\n";
	}
	
	return 0;
}