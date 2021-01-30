#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	int test_count; cin >> test_count;
	for (size_t test_no = 0; test_no < test_count; test_no++)
	{
		int n, x; cin >> n >> x;
		vector<int> starting_sequence(n);
		for (size_t i = 0; i < n; i++)
			cin >> starting_sequence[i];

		vector<int> possible_end_x = { x };
		vector<int> sorted_starting_sequence = starting_sequence;
		sort(sorted_starting_sequence.begin(), sorted_starting_sequence.end());
		vector<vector<int>> possible_end_sequences = { sorted_starting_sequence };
		for (size_t i = 0; i < n; i++)
		{
			if (starting_sequence[i] > x)
			{
				possible_end_x.push_back(starting_sequence[i]);
				vector<int> end_sequence = starting_sequence;
				end_sequence[i] = x;
				sort(end_sequence.begin(), end_sequence.end());
				possible_end_sequences.push_back(end_sequence);
			}
		}
		
		int min_swap_count = INT_MAX;
		for (size_t i = 0; i < possible_end_sequences.size(); i++)
		{
			int end_x = possible_end_x[i];
			int current_x = x;
			vector<int>& end_sequence = possible_end_sequences[i];
			vector<int> current_sequence = starting_sequence;
			int swap_count = 0;
			for (size_t position = 0; position < end_sequence.size(); position++)
			{
				if (current_x == end_x)
				{
					if (is_sorted(current_sequence.begin(),current_sequence.end()))
						min_swap_count = min(min_swap_count, swap_count);
					break;
				}
				if (current_sequence[position] != end_sequence[position])
				{
					if (current_sequence[position] > current_x)
					{
						swap(current_sequence[position], current_x);
						swap_count++;
					}
					else
						break;
				}
			}
		}
		if (min_swap_count == INT_MAX)
			cout << "-1\n";
		else
			cout << min_swap_count << "\n";
	}
	return 0;
}