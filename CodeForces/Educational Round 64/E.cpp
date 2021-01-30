#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <unordered_set>
using namespace std;
#define ll long long
#define uset unordered_set

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n; cin >> n;
	vector<int> elements(n);
	vector<int> element_position_map(n+1);
	for (size_t i = 0; i < n; i++)
	{
		cin >> elements[i];
		element_position_map[elements[i]] = i;
	}

	deque<pair<int, int>> current_elements;
	vector<ll> left_count(n), right_count(n);
	for (size_t i = 0; i < n; i++)
	{
		int new_element = elements[i];
		int new_count = 0;
		while (!current_elements.empty() && elements[current_elements.back().first] < new_element)
		{
			new_count++;
			new_count += current_elements.back().second;
			right_count[current_elements.back().first] = i - current_elements.back().first - 1;
			current_elements.pop_back();
		}
		left_count[i] = new_count;
		current_elements.push_back({ i,new_count });
	}

	while (!current_elements.empty())
	{
		right_count[current_elements.back().first] = n - current_elements.back().first - 1;
		current_elements.pop_back();
	}

	ll solution = 0;
	for (size_t i = 0; i < n; i++)
	{
		if (left_count[i] == 0 || right_count[i] == 0)
			continue;
		
		pair<int, int> segment_to_iterate = { i - left_count[i],  i - 1 }, other_segment = { i + 1 , i + right_count[i] };
		if (right_count[i] < left_count[i])
			swap(segment_to_iterate, other_segment);
		
		int max_element_value = elements[i];
		for (size_t j = segment_to_iterate.first; j <= segment_to_iterate.second; j++)
		{
			int other_element = max_element_value - elements[j];
			int other_element_position = element_position_map[other_element];

			if (other_element_position >= other_segment.first && 
				other_element_position <= other_segment.second)
				solution++;
		}
	}

	cout << solution;
	return 0;
}