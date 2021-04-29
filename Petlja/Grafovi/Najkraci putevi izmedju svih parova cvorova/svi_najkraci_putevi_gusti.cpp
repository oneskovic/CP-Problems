#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n; cin >> n;
	vector<vector<ll>> weight(n, vector<ll>(n));
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			cin >> weight[i][j];

	auto dp = weight;
	for (int i = 0; i < n; i++)
		dp[i][i] = 0;
	
	for (int k = 0; k < n; k++)
	{
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				dp[i][j] = min(dp[i][j], dp[i][k] + dp[k][j]);
			}
		}
	}

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout << weight[i][j] - dp[i][j] << " ";
		}
		cout << "\n";
	}

	return 0;
}
