#include <algorithm>
#include <iostream>
#include <limits.h>
#include <vector>
#include <string>
#include <map>
using namespace std;
typedef long long ll;


int solve(int l, int r, const vector<int>& v, vector<vector<int>>& dp)
{
	if (dp[l][r] != -1)
		return dp[l][r];
	if (l == r)
	{
		return 0;
	}
	int n = v.size();
	int min_sol = INT_MAX;
	for (int end_color: {v[l], v[r]})
	{
		int sol = INT_MAX;
		if (all_of(v.begin() + l, v.begin() + r+1, [end_color](int x) {return x == end_color;}))
		{
			sol = 0;
		}
		else
		{
			int i = l;
			while (v[i] == end_color)
				i++;
			int j = r;
			while (v[j] == end_color)
				j--;
			sol = solve(i, j, v, dp) + 1;
		}
		min_sol = min(sol, min_sol);
	}
	dp[l][r] = min_sol;
	return min_sol;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n; cin >> n;
	vector<int> v(n);
	for (int i = 0; i < n; i++)
		cin >> v[i];

	vector<vector<int>> dp = vector<vector<int>>(n, vector<int>(n, -1));
	cout << solve(0, n - 1, v, dp);
		
	return 0;
}