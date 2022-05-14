#include <algorithm>
#include <iostream>
#include <vector>
#include <chrono>
using namespace std;
typedef long long ll;

bool median_at_least(const vector<int>& v, int k, int median)
{
	int n = v.size();
	vector<int> greater_or_less(n);
	for (int i = 0; i < n; i++)
	{
		if (v[i] >= median)
			greater_or_less[i] = 1;
		else
			greater_or_less[i] = -1;
	}

	vector<int> prefix_sum(n);
	prefix_sum[0] = greater_or_less[0];
	for (int i = 1; i < n; i++)
		prefix_sum[i] = greater_or_less[i] + prefix_sum[i - 1];

	int l = 0;
	
	int min_prefix_sum = 0;
	for (int r = k - 1; r < n; r++)
	{
		if (prefix_sum[r] - min_prefix_sum > 0)
			return true;
		
		min_prefix_sum = min(min_prefix_sum,prefix_sum[l++]);
	}
	return false;
}

int solve(const vector<int>& v, int k)
{
	int n = v.size();
	int l = 0, r = n+1;
	while (r - l > 1)
	{
		int mid = (l + r) / 2;
		if (median_at_least(v,k,mid))
			l = mid;
		else
			r = mid;
	}
	return l;
}

int main()
{
	srand(time(0));
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n, k; cin >> n >> k;
	vector<int> v(n);
	for (int i = 0; i < n; i++)
		cin >> v[i];
	
	cout << solve(v, k) << "\n";
	
	return 0;
}