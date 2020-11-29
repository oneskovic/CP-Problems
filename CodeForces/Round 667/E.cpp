#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
#define ll long long

int main()
{
	ios::sync_with_stdio(false);
	int test_count; cin >> test_count;
	for (size_t test_no = 0; test_no < test_count; test_no++)
	{
		int point_count, k; cin >> point_count >> k;
		vector<ll> x_coordinates(point_count);
		for (size_t i = 0; i < point_count; i++)
			cin >> x_coordinates[i];
		
		// Y-coordinates can be ignored as it is optimal to place the platform
		// at the bottom (smallest y)
		for (size_t i = 0; i < point_count; i++)
		{
			int t; cin >> t;
		}
		sort(x_coordinates.begin(), x_coordinates.end());
		
		vector<ll> max_collected_points(point_count); // Prefix maximums (collected by the left platform)
		ll l = 0, r = 0;
		ll max_collected = 0;
		while (r < x_coordinates.size())
		{
			while (x_coordinates[r] - x_coordinates[l] > k)
				l++;

			ll currently_collected = r - l + 1;
			max_collected = max(max_collected, currently_collected);
			max_collected_points[r] = max_collected;
			r++;
		}

		// Try every position for the right platform
		r = point_count - 1, l = point_count - 1;
		ll max_collected_by_both = 0;
		while (l >= 0)
		{
			while (x_coordinates[r] - x_coordinates[l] > k)
				r--;
			ll currently_collected = r - l + 1;
			ll max_by_other_platform = 0;
			if (l > 0)
				max_by_other_platform = max_collected_points[l - 1];
			
			max_collected_by_both = max(max_collected_by_both, currently_collected + max_by_other_platform);
			l--;
		}
		cout << max_collected_by_both << "\n";
	}
	return 0;
}