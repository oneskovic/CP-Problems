#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
#define ll long long

/// <summary>
/// Check recursively if it is possible to get the given reminder 
/// using only the elements starting from the given position 
/// </summary>
vector<vector<bool>> available, computed_solutions;
bool possible_to_get(ll reminder, int starting_position, const vector<ll>& elements, int mod)
{
	if (starting_position == elements.size())
		return false;
	if (available[reminder][starting_position])
		return computed_solutions[reminder][starting_position];
	
	ll current_mod = starting_position;
	bool possible = possible_to_get(reminder, starting_position + 1, elements, mod);
	for (size_t i = 1; i <= elements[starting_position] && !possible; i++)
	{
		if (current_mod == reminder)
			possible = true;
		
		else if (possible_to_get((reminder - current_mod + mod) % mod, starting_position + 1, elements, mod))
			possible = true;
		
		current_mod += starting_position;
		current_mod %= mod;
	}

	available[reminder][starting_position] = true;
	computed_solutions[reminder][starting_position] = possible;
	return possible;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	int element_count, mod; cin >> element_count >> mod;

	// Take all given elements and "map" them to the range [0,mod) counting how many times each element appears
	// Reduces the number of elements from 10^6 to 10^3
	vector<ll> elements(mod);
	for (size_t i = 0; i < element_count; i++)
	{
		int element; cin >> element;
		elements[element % mod]++;
	}
	available = vector<vector<bool>>(mod);
	computed_solutions = vector<vector<bool>>(mod);
	for (size_t i = 0; i < mod; i++)
	{
		available[i] = vector<bool>(mod);
		computed_solutions[i] = vector<bool>(mod);
	}

	if (possible_to_get(0, 0, elements, mod))
		cout << "YES\n";
	else
		cout << "NO\n";
	return 0;
}