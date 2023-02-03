#include <algorithm>
#include <iostream>
#include <vector>
#include <limits.h>
using namespace std;
typedef long long ll;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int a, b; cin >> a >> b;
	vector<vector<int>> dp(a+1, vector<int>(b+1, INT_MAX));
	for (int i = 0; i <= min(a,b); i++)
		dp[i][i] = 0;
	
	for (int i = 1; i <= a; i++)
	{
		for (int j = 1; j <= b; j++)
		{
			for (int x = 1; x < i; x++)
				dp[i][j] = min(dp[i][j], dp[i - x][j] + dp[x][j] + 1);
			for (int x = 1; x < j; x++)
				dp[i][j] = min(dp[i][j], dp[i][j - x] + dp[i][x] + 1);
		}
	}
	cout << dp[a][b];
	return 0;
}