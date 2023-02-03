#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;

int main()
{
	freopen("diamond.in", "r", stdin);
	freopen("diamond.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n, k; cin >> n >> k;
	vector<int> v(n);
	for (int i = 0; i < n; i++)
		cin >> v[i];	

	sort(v.begin(), v.end());
	vector<int> subarray_sizes(n); // subarray size if i is the smallest diamond
	int l = 0, r = 0;
	do
	{
		while (r < n && v[r] - v[l] <= k)
			r++;
		subarray_sizes[l] = r - l;
		l++;
	} while (l < n);

	vector<int> postfix_max(n); // postfix max on subarray sizes
	postfix_max[n - 1] = subarray_sizes[n - 1];
	for (int i = n - 2; i >= 0; i--)
		postfix_max[i] = max(postfix_max[i + 1], subarray_sizes[i]);

	int sol = 0;
	for (int i = 0; i < n; i++)
	{
		int len = subarray_sizes[i];
		int current_sol = len + (i + len < n ? postfix_max[i + len] : 0);
		sol = max(sol, current_sol);
	}
	cout << sol;

	return 0;
}