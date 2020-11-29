#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <numeric>
using namespace std;
#define ll long long

ll can_get_all_in_time(const vector<ll>& delivery, const vector<ll>& pickup, ll time)
{
	size_t n = delivery.size();
	ll time_to_pickup = 0;
	for (size_t i = 0; i < n; i++)
	{
		if (delivery[i] > time)
			time_to_pickup += pickup[i];
	}
	return time_to_pickup <= time;
}

ll find_minimal_time(const vector<ll>& delivery, const vector<ll>& pickup)
{
	ll left = 0, right = *max_element(delivery.begin(), delivery.end()) + 1;
	while (right-left > 1)
	{
		ll mid = (left + right) / 2;
		if (can_get_all_in_time(delivery,pickup,mid))
			right = mid;
		else
			left = mid;
	}
	return right;
}

int main()
{
	ios::sync_with_stdio(false);
	int test_count; cin >> test_count;
	for (size_t test_no = 0; test_no < test_count; test_no++)
	{
		int n; cin >> n;
		vector<ll> delivery_times(n), pickup_times(n);
		for (size_t i = 0; i < n; i++)
			cin >> delivery_times[i];

		for (size_t i = 0; i < n; i++)
			cin >> pickup_times[i];
		cout << find_minimal_time(delivery_times, pickup_times) << "\n";
	}
	return 0;
}