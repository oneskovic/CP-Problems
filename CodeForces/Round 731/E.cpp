#include <algorithm>
#include <iostream>
#include <vector>
#include <set>
using namespace std;
typedef long long ll;
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	int test_cnt; cin >> test_cnt;
	while (test_cnt--)
	{
		int n, k; cin >> n >> k;
		vector<int> positions(k);
		vector<ll> temps(n);
		vector<bool> has_ac(n);
		for (int i = 0; i < k; i++)
		{
			cin >> positions[i];
			positions[i]--;
			has_ac[positions[i]] = 1;
		}
		for (int i = 0; i < k; i++)
		{
			ll temp; cin >> temp;
			temps[positions[i]] = temp;
		}
		multiset<ll> values_left, values_right;
		for (int i = 0; i < positions.size(); i++)
		{
			values_right.insert(positions[i] + temps[positions[i]]);
		}

		ll delta_left = 0, delta_right = 0;
		for (int i = 0; i < n; i++)
		{
			ll min_left = values_left.empty() ? LLONG_MAX : *values_left.begin() + delta_left;
			ll min_right = values_right.empty() ? LLONG_MAX : * values_right.begin() + delta_right;
			cout << min(min_left, min_right) << " ";
			if (has_ac[i])
			{
				values_left.insert(temps[i] - delta_left);
				values_right.erase(values_right.find(temps[i] + i));
			}
			delta_left++;
			delta_right--;
		}
	}
	return 0;
}