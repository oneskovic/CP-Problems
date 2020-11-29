#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;
#define ll long long
int main()
{
	ios::sync_with_stdio(false);

	int test_count; cin >> test_count;
	for (size_t test_no = 0; test_no < test_count; test_no++)
	{
		int n; cin >> n;
		unordered_map<ll, int> nodes_count;
		vector<ll> nodes(n);
		for (size_t i = 0; i < n; i++)
		{
			cin >> nodes[i];
			nodes_count[nodes[i]]++;
		}
		if (all_of(nodes.begin(), nodes.end(), [nodes](int a) {return a == nodes[0]; }))
		{
			cout << "NO\n";
		}
		else
		{
			int min_count = INT_MAX;
			ll min_elem = -1;
			for (const auto& kvp: nodes_count)
			{
				if (kvp.second < min_count)
				{
					min_count = kvp.second;	
					min_elem = kvp.first;
				}
			}
			
			int min_elem_first_pos = find(nodes.begin(), nodes.end(), min_elem) - nodes.begin();
			int other_elem_pos = find_if(nodes.begin(), nodes.end(), [min_elem](int a) {return a != min_elem; }) - nodes.begin();

			cout << "YES\n";
			for (size_t i = 0; i < n; i++)
			{
				if (nodes[i] != min_elem)
				{
					cout << i+1 << " " << min_elem_first_pos+1 << "\n";
				}
				else if(i != min_elem_first_pos)
				{
					cout << i+1 << " " << other_elem_pos+1 << "\n";
				}
			}			
		}
	}
	return 0;
}