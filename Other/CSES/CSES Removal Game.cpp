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
	vector<int> elements(n);
	for (int i = 0; i < n; i++)
		cin >> elements[i];

	vector<vector<ll>> dp1(n, vector<ll>(n));
	auto dp2 = dp1;
	for (int i = 0; i < n; i++)
		dp1[i][i] = elements[i];
	for (int offset = 1; offset < n; offset++)
	{
		for (int i = 0; i < n-offset; i++)
		{
			int col = i + offset;
			dp1[i][col] = max(dp2[i + 1][col] + elements[i], dp2[i][col - 1] + elements[col]);
			dp2[i][col] = min(dp1[i + 1][col], dp1[i][col - 1]);
		}
	}
	cout << dp1[0][n-1];

	return 0;
}