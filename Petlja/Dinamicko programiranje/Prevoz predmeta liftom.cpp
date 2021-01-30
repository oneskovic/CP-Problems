#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

struct dp_solution
{
	int remaining_weight;
	int no_rides;
};
inline bool operator< (const dp_solution& lhs, const dp_solution& rhs)
{
	if (lhs.no_rides < rhs.no_rides)
	{
		return true;
	}
	else
	{
		return lhs.remaining_weight > rhs.remaining_weight;
	}
}

int count_ones (int subset)
{
	int mask = 1;
	int count = 0;
	for (size_t i = 0; i < 20; i++)
	{
		if (subset & mask)
			count++;
		mask <<= 1;
	}
	return count;
}

bool is_bit_set(int subset, int bit_position)
{
	return (subset & (1 << bit_position));
}

int unset_bit(int subset, int bit_position)
{
	return (subset ^ (1 << bit_position));
}

int main()
{
	int n; cin >> n;
	vector<int> weights(n);
	for (size_t i = 0; i < n; i++)
		cin >> weights[i];
	
	int max_weight; cin >> max_weight;
	vector<dp_solution> dp(1 << (n+1));
	dp[0] = { max_weight,1 };
	vector<vector<int>> subsets(n+2);
	for (int i = 1; i < (1 << (n+1)); i++)
	{
		subsets[count_ones(i)].push_back(i);
	}

	for (size_t item_count = 1; item_count <= n; item_count++)
	{
		for (int subset: subsets[item_count])
		{
			dp_solution solution_for_subset = { -1,INT_MAX };
			for (size_t item_index = 0; item_index < n; item_index++)
			{
				if (is_bit_set(subset,item_index))
				{
					dp_solution solution_with_item;
					auto solution_without_item = dp[unset_bit(subset,item_index)];
					if (solution_without_item.remaining_weight >= weights[item_index])
					{
						solution_with_item.remaining_weight = solution_without_item.remaining_weight - weights[item_index];
						solution_with_item.no_rides = solution_without_item.no_rides;
					}
					else
					{
						solution_with_item.remaining_weight = max_weight - weights[item_index];
						solution_with_item.no_rides = solution_without_item.no_rides + 1;
					}
					solution_for_subset = min(solution_for_subset, solution_with_item);
				}
			}
			dp[subset] = solution_for_subset;
		}
	}
	cout << dp[(1 << n) - 1].no_rides;
	
	return 0;
}