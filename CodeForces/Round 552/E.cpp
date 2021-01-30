#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <list>
using namespace std;

bool has_left_element(const list<int>& l, list<int>::iterator it)
{
	return it != l.begin();
}

bool has_right_element(const list<int>& l, list<int>::iterator it)
{
	return it != --l.end();
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n, k;
	cin >> n >> k;
	list<int> elements;
	vector<int> elements_vector(n);
	map<int, list<int>::iterator, greater<int>> value_iterator_map;
	for (size_t i = 0; i < n; i++)
	{
		int element; cin >> element;
		elements.push_back(element);
		elements_vector[i] = element;
		value_iterator_map[element] = --elements.end();
	}
	
	map<int, int> element_team_map;
	int current_team = 0;
	while (!value_iterator_map.empty())
	{
		auto max_value_it = value_iterator_map.begin()->second;
		auto current_it = max_value_it;
		for (size_t i = 0; i < k && has_left_element(elements, current_it); i++)
		{
			current_it--;
			element_team_map[*current_it] = current_team;
			value_iterator_map.erase(*current_it);
			current_it = elements.erase(current_it);
		}

		for (size_t i = 0; i < k && has_right_element(elements, current_it); i++)
		{
			current_it++;
			element_team_map[*current_it] = current_team;
			value_iterator_map.erase(*current_it);
			current_it = --elements.erase(current_it);
		}

		element_team_map[*max_value_it] = current_team;
		value_iterator_map.erase(*max_value_it);
		elements.erase(max_value_it);

		current_team = (current_team + 1) % 2;
	}

	for (int element: elements_vector)
		cout << element_team_map[element]+1;
	
	cout << "\n";
	return 0;
}