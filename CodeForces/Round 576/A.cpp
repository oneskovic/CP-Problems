#include <iostream>
#include <algorithm>
#include <vector>
#include <limits>
using namespace std;
#define ll long long

int main()
{
	ios::sync_with_stdio(false);
	ll n, bytes;
	cin >> n >> bytes;
	ll k = bytes * 8 / n;
	if (k >= ceil(log2(n)))
	{
		k = ceil(log2(n));
	}
	ll max_distinct_count = pow(2, k);

	vector<ll> values(n);
	for (size_t i = 0; i < n; i++)
		cin >> values[i];
	sort(values.begin(), values.end());

	int l = 0, r = 0;
	int min_removed = INT_MAX;
	int distinc_count = 1;
	while (l < n)
	{
		while (distinc_count < max_distinct_count && r < n-1)
		{
			r++;
			if (values[r] != values[r-1])
				distinc_count++;
		}
		if (distinc_count <= max_distinct_count)
		{
			while (r < n-1 && values[r+1] == values[r])
				r++;
		
			int removed = l + n-1-r;
			min_removed = min(min_removed, removed);
		}
		while (l < n-1 && values[l] == values[l+1])
			l++;
		l++;
		
		distinc_count--;
	}
	cout << min_removed << "\n";
	return 0;
}