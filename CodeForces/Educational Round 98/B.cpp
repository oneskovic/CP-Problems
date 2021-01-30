#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
#define ll long long
int main()
{
	int test_count; cin >> test_count;
	for (size_t test_no = 0; test_no < test_count; test_no++)
	{
		int n; cin >> n;
		ll sum = 0;
		ll max_element = LLONG_MIN;
		for (size_t i = 0; i < n; i++)
		{
			ll element; cin >> element;
			sum += element;
			max_element = max(max_element, element);
		}
		ll min_per_box = max(max_element, (ll)ceil(sum * 1.0 / (n - 1)));
		ll solution = min_per_box * (n - 1) - sum;
		cout << solution << "\n";
	}
	return 0;
}