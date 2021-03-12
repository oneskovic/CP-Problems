#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>
#include <map>

using namespace std;
#define ll long long
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int test_count; cin >> test_count;
	for (size_t test_no = 0; test_no < test_count; test_no++)
	{
		int n; cin >> n;
		vector<ll> elements(n);
		map<ll, vector<int>> prefix_sum_zeros;
		for (size_t i = 0; i < n; i++)
			cin >> elements[i];
		ll current_sum = 0;
		for (size_t i = 0; i < n; i++)
		{
			current_sum += elements[i];
			prefix_sum_zeros[current_sum] = vector<int>();
		}

		ll prefix_sum_offset = 0;
		ll left = 0;

		for (size_t i = 0; i < n; i++)
		{
			left = elements[i];
			prefix_sum_offset += elements[i];
			if (prefix_sum_zeros.find(-left + prefix_sum_offset) != prefix_sum_zeros.end())
			{
				prefix_sum_zeros[-left + prefix_sum_offset].push_back(i);
			}
		}

		vector<int> zeros(n);
		current_sum = 0;
		for (size_t i = 0; i < n; i++)
		{
			current_sum += elements[i];
			auto it = lower_bound(prefix_sum_zeros[current_sum].begin(), prefix_sum_zeros[current_sum].end(), i);
			zeros[i] = it - prefix_sum_zeros[current_sum].begin();
		}

		ll solution = 1;
		for (size_t i = 1; i < n; i++)
		{
			solution *= 2;
			solution -= zeros[i - 1];
		}

		cout << solution;
	}
	return 0;
}