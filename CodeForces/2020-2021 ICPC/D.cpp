#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
#define ll long long

bool check(const vector<ll>& times, int count, int remaining_time)
{
	for (int i = count; i > 0; i--)
	{
		remaining_time--;
		if (times[i-1] > remaining_time)
		{
			return false;
		}
	}
	return true;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	int test_count; cin >> test_count;
	for (size_t test_no	= 0; test_no < test_count; test_no++)
	{
		ll coridor_length, firecracker_count, a, b;
		cin >> coridor_length >> firecracker_count >> a >> b;
		int total_time = abs(a - b) - 1;
		if (a < b)
			total_time += a;
		else
			total_time += coridor_length - a + 1;

		vector<ll> firecracker_times(firecracker_count);
		for (size_t i = 0; i < firecracker_count; i++)
			cin >> firecracker_times[i];
		sort(firecracker_times.begin(), firecracker_times.end());

		
		int l = 1, r = min(abs(a - b)-1, firecracker_count);
		while (l <= r)
		{
			int mid = (l + r) / 2;
			if (check(firecracker_times, mid, total_time))
			{
				l = mid + 1;
			}
			else
			{
				r = mid - 1;
			}
		}
		int solution = (l + r) / 2;
		cout << solution << "\n";
	}
	return 0;
}