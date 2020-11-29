#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;
#define ll long long

ll solve(string elements, int activate_cost, int place_cost)
{
	if (find(elements.begin(), elements.end(), '1') == elements.end()) // All elements are zeros
		return 0;

	vector<int> distances; distances.reserve(elements.size());
	bool currently_in_segment = false;
	int previous_segment_position = -1;
	for (size_t i = 0; i < elements.size(); i++)
	{
		if (elements[i] == '1')
		{
			if (previous_segment_position != -1 && !currently_in_segment)
				distances.push_back(i - previous_segment_position - 1);
			
			currently_in_segment = true;
			previous_segment_position = i;
		}
		else
			currently_in_segment = false;
	}

	ll total_cost = activate_cost;
	for (size_t i = 0; i < distances.size(); i++)
	{
		int price_to_merge = distances[i] * place_cost;
		int price_to_not_merge = activate_cost;
		total_cost += min(price_to_merge, price_to_not_merge);
	}
	return total_cost;
}

int main()
{
	ios::sync_with_stdio(false);
	int test_count; cin >> test_count;
	for (size_t test_no = 0; test_no < test_count; test_no++)
	{
		int activate_cost, place_cost; cin >> activate_cost >> place_cost;
		string elements; cin >> elements;
		cout << solve(elements, activate_cost, place_cost) << "\n";
	}
	return 0;
}