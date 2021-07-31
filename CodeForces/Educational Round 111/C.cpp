#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>
using namespace std;
typedef long long ll;

bool check(const vector<ll>& v)
{
	int n = v.size();
	for (int i = 0; i < n; i++)
	{
		for (int j = i+1; j < n; j++)
		{
			for (int k = j+1; k < n; k++)
			{
				vector<ll> temp = { v[i],v[j],v[k] };
				vector<ll> temp_reversed = { v[k],v[j],v[i] };
				if (is_sorted(temp.begin(),temp.end()) || is_sorted(temp_reversed.begin(),temp_reversed.end()))
				{
					return false;
				}
			}
		}
	}
	return true;
}

ll count_good_subarrays(int length, const vector<ll>& y)
{
	int n = y.size();
	ll count_good = 0;
	for (int left = 0; left <= n-length; left++)
	{
		vector<ll> subarray_y(y.begin() + left, y.begin() + left + length);
		if (check(subarray_y))
		{
			count_good++;
		}
	}
	return count_good;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	int t; cin >> t;
	while (t--)
	{
		int n; cin >> n;
		vector<ll> y(n);
		for (int i = 0; i < n; i++)
			cin >> y[i];
		cout << count_good_subarrays(3, y) + count_good_subarrays(4, y) + n + n - 1 << "\n";
	}
	return 0;
}