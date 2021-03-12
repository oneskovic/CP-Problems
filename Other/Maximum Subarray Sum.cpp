#include <algorithm>
#include <iostream>
#include <vector>
#include <climits>

using namespace std;
#define ll long long

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n; cin >> n;
	vector<ll> elements(n+1);
	for (size_t i = 1; i <= n; i++)
		cin >> elements[i];

	vector<ll> prefix_sum(n+1);
	prefix_sum[0] = 0;

	ll min_left_prefix = prefix_sum[0];
	ll max_subarray_sum = LLONG_MIN;
	for (size_t i = 1; i <= n; i++)
	{
		prefix_sum[i] = prefix_sum[i - 1] + elements[i];
		ll current_sum = prefix_sum[i] - min_left_prefix;
		max_subarray_sum = max(max_subarray_sum, current_sum);
		min_left_prefix = min(min_left_prefix, prefix_sum[i]);
	}
	cout << max_subarray_sum;
	return 0;
}