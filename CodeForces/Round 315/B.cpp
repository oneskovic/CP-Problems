#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
#define ll long long
const ll mod = 1e9 + 7;

vector<vector<ll>> computed_values_eq;

inline void mod_add(ll& a, ll b)
{
	a %= mod;
	b %= mod;
	a += b;
	a %= mod;
}

inline void mod_mul(ll& a, ll b)
{
	a %= mod;
	b %= mod;
	a *= b;
	a %= mod;
}

/// <summary>
/// Computes the number of ways to create equivalence relations with the given number
/// of elements by creating exactly the given number of equivalence classes
/// </summary>
ll number_of_equivalence(int element_count, int classes_count)
{
	if (element_count < classes_count)
		return 0;
	if (classes_count == 1)
		return 1;
	if (computed_values_eq[element_count][classes_count] > -1)
		return computed_values_eq[element_count][classes_count];
	
	ll value = number_of_equivalence(element_count - 1, classes_count);
	mod_mul(value, classes_count);
	mod_add(value, number_of_equivalence(element_count - 1, classes_count - 1));
	computed_values_eq[element_count][classes_count] = value;
	return value;
}

ll number_of_equivalence(int element_count)
{
	if (element_count == 0)
		return 1;
	
	ll solution = 0;
	for (size_t i = 1; i <= element_count; i++)
		mod_add(solution, number_of_equivalence(element_count, i));
	
	return solution;
}

vector<vector<ll>> computed_values_nk;

ll n_choose_k(ll n, ll k)
{
	if (n == k)
		return 1;
	if (k == 1)
		return n;
	
	if (computed_values_nk[n][k] > -1)
		return computed_values_nk[n][k];
	ll value = n_choose_k(n - 1, k);
	mod_add(value, n_choose_k(n - 1, k - 1));
	computed_values_nk[n][k] = value;
	return value;
}



int main()
{
	int n; cin >> n;

	computed_values_eq = vector<vector<ll>>(n + 1);
	computed_values_nk = vector<vector<ll>>(n + 1);

	for (size_t i = 0; i <= n; i++)
	{
		computed_values_eq[i] = vector<ll>(n + 1, -1);
		computed_values_nk[i] = vector<ll>(n + 1, -1);
	}

	ll solution = 0;
	for (size_t i = 0; i < n; i++)
	{
		ll temp = n_choose_k(n, n-i);
		mod_mul(temp, number_of_equivalence(i));
		mod_add(solution, temp);
	}
	cout << solution;
	return 0;
}