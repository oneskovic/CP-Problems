#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
using namespace std;
typedef long long ll;
const int mod = 1e9 + 7;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n; cin >> n;
	vector<vector<bool>> is_trap(n, vector<bool>(n));
	for (int i = 0; i < n; i++)
	{
		string s; cin >> s;
		for (int j = 0; j < n; j++)
			is_trap[i][j] = (s[j] == '*');
	}
	vector<vector<int>> dp(n, vector<int>(n));
	// Fill first row
	dp[0][0] = !is_trap[0][0];
	for (int col = 1; col < n; col++)
		if (!is_trap[0][col])
			dp[0][col] = dp[0][col - 1];
	
	// Fill first column
	for (int row = 1; row < n; row++)
		if (!is_trap[row][0])
			dp[row][0] = dp[row - 1][0];
	
	for (int row = 1; row < n; row++)
		for (int col = 1; col < n; col++)
			if (!is_trap[row][col])
				dp[row][col] = (dp[row - 1][col] + dp[row][col - 1]) % mod;
		
	cout << dp[n-1][n-1];
	return 0;
}