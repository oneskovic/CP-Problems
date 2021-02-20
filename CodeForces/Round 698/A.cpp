#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int test_count; cin >> test_count;
	for (size_t test_no = 0; test_no < test_count; test_no++)
	{
		int n; cin >> n;
		vector<int> element_count(n + 1);
		for (size_t i = 0; i < n; i++)
		{
			int element; cin >> element;
			element_count[element]++;
		}
		cout << *max_element(element_count.begin(), element_count.end()) << "\n";
	}
	return 0;
}