#include <algorithm>
#include <iostream>
#include <limits.h>
#include <vector>
using namespace std;
typedef long long ll;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n; cin >> n;
	ll max_weight; cin >> max_weight;
	vector<ll> weights(n);
	for (int i = 0; i < n; i++)
		cin >> weights[i];
	reverse(weights.begin(), weights.end());

	vector<int> dp_rides(1 << n, INT_MAX);
	vector<ll> dp_remaining_space(1 << n, 0);
	dp_rides[0] = 0;
	dp_remaining_space[0] = 0;
	for (int subset = 1; subset < (1<<n); subset++)
	{
		for (int j = 0, mask = 1; j < n; j++, mask <<= 1)
		{
			if (mask & subset)
			{
				int rides_without_person = dp_rides[subset ^ mask];
				ll space_without_person = dp_remaining_space[subset ^ mask];
				if (weights[j] <= space_without_person && rides_without_person <= dp_rides[subset])
				{
					dp_rides[subset] = rides_without_person;
					dp_remaining_space[subset] = max(dp_remaining_space[subset], space_without_person - weights[j]);
				}
				else if (rides_without_person + 1 <= dp_rides[subset])
				{
					dp_rides[subset] = rides_without_person + 1;
					dp_remaining_space[subset] = max(dp_remaining_space[subset], max_weight - weights[j]);
				}
			}
		}
	}
	cout << dp_rides[(1 << n) - 1];

	return 0;
}