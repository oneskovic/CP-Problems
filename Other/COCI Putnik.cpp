#include <algorithm>
#include <iostream>
#include <limits.h>
#include <vector>
#include <string>
using namespace std;
typedef long long ll;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);


	int n; cin >> n;
	vector<vector<int>> w(n, vector<int>(n,3));
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			cin >> w[i][j];
	int inf = 1500000;
	vector<vector<int>> dp(n, vector<int>(n, inf));
	vector<vector<int>> last_visit(n, vector<int>(n, 0));
	dp[0][0] = 0;
	for (int i = 1; i < n; i++)
	{
		// [1,2,...,i-1] i
		for (int l = 0; l < i; l++)
		{
			if (l == i-1)
			{
				// l [1,2,..., i-1] x i
				int v = inf;
				for (int x = 0; x < i; x++)
				{
					if (last_visit[l][x] == i - 1)
						v = min(v, dp[l][x] + w[x][i]);
				}
				dp[l][i] = v;
				if (v != inf)
				{
					last_visit[l][i] = i;
				}
			}
			else
			{
				int v = inf;
				for (int x : {i-1})
				{
					if (last_visit[l][x] == i - 1)
						v = min(v, dp[l][x] + w[x][i]);
				}
				dp[l][i] = v;
				if (v != inf)
				{
					last_visit[l][i] = i;
				}
			}
		}

		
		// i [1,2,...,i-1]
		for (int r = 0; r < i; r++)
		{
			if (r == i-1)
			{
				// i x [1,2,...i-1] r
				int v = inf;
				for (int x = 0; x < i; x++)
				{
					if (last_visit[x][r] == i - 1)
						v = min(v, dp[x][r] + w[i][x]);
				}
				dp[i][r] = v;
				if (v != inf)
				{
					last_visit[i][r] = i;
				}
			}
			else
			{
				// i x [1,2,...i-1] r
				int v = inf;
				for (int x : {i-1})
				{
					if (last_visit[x][r] == i - 1)
						v = min(v, dp[x][r] + w[i][x]);
				}
				dp[i][r] = v;
				if (v != inf)
				{
					last_visit[i][r] = i;
				}
			}

		}
	}
	
	int sol = inf;
	for (int i = 0; i < n; i++)
		sol = min(sol, dp[i][n - 1]);
	for (int i = 0; i < n; i++)
		sol = min(sol, dp[n - 1][i]);
	cout << sol << "\n";

	return 0;
}