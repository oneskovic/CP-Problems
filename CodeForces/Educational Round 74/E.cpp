#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_set>
#include <string>
#include <map>
using namespace std;

vector<int> dp;
vector<vector<int>> counts;

inline bool is_bit_set(int n, int bit_position)
{
	return (n & (1 << bit_position));
}

inline int unset_bit(int n, int bit_position)
{
	return (n ^ (1 << bit_position));
}

int to_int(const vector<bool>& v)
{
	int result = 0;
	int mask = 1;
	for (size_t i = 0; i < v.size(); i++)
	{
		if (v[i])
		{
			result |= mask;
		}
		mask <<= 1;
	}
	return result;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n, m; cin >> n >> m;
	string s; cin >> s;

	counts = vector<vector<int>>(30, vector<int>(30));
	for (size_t i = 1; i < n; i++)
	{
		int current_char = s[i] - 'a';
		int previous_char = s[i - 1] - 'a';
		counts[previous_char][current_char]++;
		counts[current_char][previous_char]++;
	}

	vector<int> dp = vector<int>(1 << m, INT_MAX);
	dp[0] = 0;
	auto possible_sets = vector<vector<int>>(m+1);
	
	for (size_t ones_count = 0; ones_count <= m; ones_count++)
	{
		vector<bool> set = vector<bool>(m-ones_count);
		for (size_t i = 0; i < ones_count; i++)
			set.push_back(1);
		do
		{
			possible_sets[ones_count].push_back(to_int(set));
		} while (next_permutation(set.begin(),set.end()));
	}


	for (size_t ones_count = 1; ones_count <= m; ones_count++)
	{
		for (auto chosen_elements: possible_sets[ones_count])
		{
			int min_value = INT_MAX;
			for (size_t char_to_set = 0; char_to_set < m; char_to_set++)
			{
				if (is_bit_set(chosen_elements,char_to_set))
				{
					int new_value = dp[unset_bit(chosen_elements,char_to_set)];
					for (size_t other_char = 0; other_char < m; other_char++)
					{
						if (other_char == char_to_set)
							continue;
						if (is_bit_set(chosen_elements,other_char))
						{
							new_value += counts[char_to_set][other_char] * (ones_count-1);
						}
						else
						{
							new_value -= counts[char_to_set][other_char] * (ones_count - 1);
						}
					}
					min_value = min(min_value, new_value);
				}
			}
			dp[chosen_elements] = min_value;
		}
	}
	cout << dp[possible_sets.back()[0]];
	return 0;
}