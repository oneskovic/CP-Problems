#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <numeric>
using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	int test_count; cin >> test_count;
	for (size_t test_no = 0; test_no < test_count; test_no++)
	{
		int n; cin >> n;
		vector<int> elements(n);
		unordered_map<int, int> element_count;
		for (size_t i = 0; i < n; i++)
			cin >> elements[i];
		
		auto it = unique(elements.begin(), elements.end());
		elements.erase(it, elements.end());
		
		for (size_t i = 0; i < elements.size(); i++)
			element_count[elements[i]]++;

		int min_operations = INT_MAX;
		for (auto kvp: element_count)
		{
			int number_of_operations = kvp.second + 1;
			if (elements[0] == kvp.first)
				number_of_operations--;
			if (elements.back() == kvp.first)
				number_of_operations--;
			min_operations = min(min_operations, number_of_operations);
		}
		cout << min_operations << "\n";
	}
	return 0;
}