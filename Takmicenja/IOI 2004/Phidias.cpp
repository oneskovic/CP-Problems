#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	
	int w, h; cin >> w >> h;
	vector<vector<int>> dp(w + 1, vector<int>(h + 1));
	for (int i = 1; i <= w; i++)
		for (int j = 1; j <= h; j++)
			dp[i][j] = i * j;
	int n; cin >> n;
	for (int i = 0; i < n; i++)
	{
		int plate_w, plate_h; cin >> plate_w >> plate_h;
		dp[plate_w][plate_h] = 0;
	}

	for (int width = 1; width <= w; width++)
	{
		for (int height = 1; height <= h; height++)
		{
			for (int i = 1; i <= width-1; i++)
			{
				dp[width][height] = min(dp[width][height], dp[i][height] + dp[width - i][height]);
			}
			for (int i = 1; i <= height; i++)
			{
				dp[width][height] = min(dp[width][height], dp[width][i] + dp[width][height - i]);
			}
		}
	}
	cout << dp[w][h];
	return 0;
}