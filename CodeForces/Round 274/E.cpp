#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>
using namespace std;
#define ll long long
const ll mod = 1e9 + 7;

void prefix_sum(const vector<ll>& elements, vector<ll>& prefixes)
{
	ll current_sum = 0;
	for (size_t i = 0; i < elements.size(); i++)
	{
		current_sum += elements[i] % mod;
		current_sum %= mod;
		prefixes[i] = current_sum;
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	int floor_count, start_floor, forbidden_floor, k;
	cin >> floor_count >> start_floor >> forbidden_floor >> k;
	if (forbidden_floor < start_floor)
	{
		// translate the problem to the version where forbidden_floor > start_floor
		int distance = start_floor - forbidden_floor;
		start_floor = floor_count - start_floor + 1;
		forbidden_floor = start_floor + distance;
	}
	start_floor--; forbidden_floor--;

	vector<ll> computed_values(floor_count);
	for (int i = 0; i < floor_count; i++)
	{
		if (i == start_floor)
			continue;
		if (abs(i - start_floor) < abs(start_floor - forbidden_floor))
			computed_values[i] = 1;
	}
	vector<ll> prefix_sums(floor_count);
	prefix_sum(computed_values, prefix_sums);

	for (size_t num_lifts = 2; num_lifts <= k; num_lifts++)
	{
		computed_values = vector<ll>(floor_count);
		for (size_t i = 0; i < forbidden_floor; i++)
		{
			if (i > 0)
				computed_values[i] = prefix_sums[i - 1];
			int right_boundary = ceil((forbidden_floor + i) / 2.0);
			right_boundary--; // last included floor
			computed_values[i] += prefix_sums[right_boundary] - prefix_sums[i];
			computed_values[i] %= mod;
			computed_values[i] += mod;
			computed_values[i] %= mod;
		}
		prefix_sum(computed_values, prefix_sums);
	}
	cout << prefix_sums[floor_count - 1];
	return 0;
}