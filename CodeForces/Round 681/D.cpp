#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <list>
using namespace std;

#define ll long long
const ll M = 998244353;

int main()
{
	ios::sync_with_stdio(false);
	int test_count; cin >> test_count;
	for (size_t test_no = 0; test_no < test_count; test_no++)
	{
		int starting_elements_count, target_elements_count;
		cin >> starting_elements_count >> target_elements_count;
		
		// Read all elements of the first (starting) array, add them to the map and the list
		unordered_map<int, list<int>::iterator> iterator_for_element;
		list<int> starting_elements;
		for (size_t i = 0; i < starting_elements_count; i++)
		{
			int element; cin >> element;
			starting_elements.push_back(element);
			auto element_iterator = starting_elements.end();
			iterator_for_element[element] = --element_iterator;
		}

		// Read all elements of the target array, and add them to the set
		vector<int> target_elements(target_elements_count);
		unordered_set<int> target_elements_set;
		for (size_t i = 0; i < target_elements_count; i++)
		{
			int element; cin >> element;
			target_elements[i] = element;
			target_elements_set.insert(element);
		}

		ll solution = 1;
		for (size_t i = 0; i < target_elements_count; i++)
		{
			bool can_remove_left = false, can_remove_right = false;
			int target_element = target_elements[i];
			auto target_iterator = iterator_for_element[target_element];

			// Check if the left element can be removed
			if (target_iterator != starting_elements.begin())
			{
				int previous_element = *(--target_iterator);
				can_remove_left = target_elements_set.find(previous_element) == target_elements_set.end();
				target_iterator++;
			}

			// Check if the right element can be removed
			target_iterator++;
			if (target_iterator != starting_elements.end())
			{
				int next_element = *target_iterator;
				can_remove_right = target_elements_set.find(next_element) == target_elements_set.end();
			}
			target_iterator--;

			if (can_remove_left)
			{
				if (can_remove_right)
				{
					// Either left or the right element can be erased
					solution *= 2;
					solution %= M;
				}
				// Erase the left element
				starting_elements.erase(--target_iterator);
				// The target element has been added, erase it from the set
				target_elements_set.erase(target_element);				
			}
			else if (can_remove_right)
			{
				// Erase the left element
				starting_elements.erase(++target_iterator);
				// The target element has been added, erase it from the set
				target_elements_set.erase(target_element);
			}
			else
			{
				solution = 0;
				break;
			}
		}
		cout << solution % M << "\n";
	}
	return 0;
}