#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;

ll calculate_duration(const vector<ll>& counts)
{
	return counts[0] * 1 + counts[1] * 2 + counts[2] * 3;
}

ll find_min(const vector<ll>& counts, vector<ll>& a, vector<ll>& b, int pos)
{
	if (pos >= counts.size())
	{
		return abs(calculate_duration(a) - calculate_duration(b));
	}
	ll min_value = LLONG_MAX;
	for (int i = 0; i < 10; i++)
	{
		if (counts[pos]-i >= 0)
		{
			a[pos] = (counts[pos]-i)/2 + i;
			b[pos] = (counts[pos] - i) / 2;
			if (a[pos] + b[pos] == counts[pos])
			{
				min_value = min(min_value, find_min(counts, a, b, pos + 1));
				swap(a[pos], b[pos]);
				min_value = min(min_value, find_min(counts, a, b, pos + 1));
			}
		}
	}
	return min_value;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int test_cnt; cin >> test_cnt;
	while (test_cnt--)
	{
		vector<ll> counts(3);
		cin >> counts[0] >> counts[1] >> counts[2];
		vector<ll> a(3), b(3);
		ll min_diff = find_min(counts, a, b, 0);
		cout << min_diff << "\n";
	}

	return 0;
}