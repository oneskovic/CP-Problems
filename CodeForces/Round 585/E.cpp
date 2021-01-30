#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
#define ll long long

vector<vector<ll>> count_needed_swaps(const vector<int>& elements)
{
	vector<vector<ll>> needed_to_swap(21, vector<ll>(21));
	vector<ll> suffix_counts(21);
	for (size_t i = 0; i < elements.size(); i++)
		suffix_counts[elements[i]]++;
	
	for (size_t i = 0; i < elements.size(); i++)
	{
		int current_element = elements[i];
		for (int other_element = 0; other_element <= 20; other_element++)
		{
			if (other_element != current_element)
			{
				needed_to_swap[current_element][other_element] += suffix_counts[other_element];
			}
		}
		suffix_counts[current_element]--;
	}
	return needed_to_swap;
}

int to_int(const vector<bool>& v)
{
	int result = 0;
	int mask = 1;
	for (size_t i = 0; i < v.size(); i++)
	{
		if (v[i])
			result |= mask;
		
		mask <<= 1;
	}
	return result;
}

int unset_bit(int n, int bit_position)
{
	return (n ^ (1 << bit_position));
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	
	int n; cin >> n;
	vector<int> elements(n);
	for (size_t i = 0; i < n; i++)
	{
		cin >> elements[i];
	}
	// Moves needed to swap all elements i with all elements j
	// eg. {i,x,y,j,x,i,x,j} -> 3 
	auto needed_to_swap = count_needed_swaps(elements);

	vector<ll> dp(1<<21);
	// Fill base-case
	int set = 1;
	for (size_t i = 0; i <= 20; i++)
	{
		dp[set] = 0;
		set <<= 1;
	}


	for (size_t element_count = 2; element_count <= 21; element_count++)
	{
		auto set = vector<bool>(21, true);
		for (size_t i = 0; i < 21 - element_count; i++)
			set[i] = 0;
		
		do
		{
			int set_as_int = to_int(set);
			ll min_value = LLONG_MAX;
			for (size_t current_element = 0; current_element <= 20; current_element++)
			{
				if (set[current_element])
				{
					ll total_swaps = 0;
					for (size_t other_element = 0; other_element <= 20; other_element++)
						if (other_element != current_element && set[other_element])
							total_swaps += needed_to_swap[current_element][other_element];
					
					min_value = min(min_value, dp[unset_bit(set_as_int, current_element)] + total_swaps);
				}
			}
			dp[set_as_int] = min_value;
		} while (next_permutation(set.begin(), set.end()));
	}
	cout << dp[(1 << 21) - 1];
	return 0;
}