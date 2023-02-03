#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;

int main()
{
	freopen("lazy.in", "r", stdin);
	freopen("lazy.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n, k; cin >> n >> k;
	vector<vector<int>> values(n, vector<int>(n));
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			cin >> values[i][j];

	vector<vector<int>> prefix_sum_cols(n,vector<int>(n));
	for (int col = 0; col < n; col++)
	{
		prefix_sum_cols[col][0] = values[0][col];
		for (int row = 1; row < n; row++)
			prefix_sum_cols[col][row] = values[row][col] + prefix_sum_cols[col][row - 1];
	}

	int solution = 0;
	for (int row = 0; row < n; row++)
	{
		for (int col = 0; col < n; col++)
		{
			int sum = 0;
			for (int i = 0; i <= k && col+i < n; i++)
			{
				int upper = row - k + i;
				int lower = min(row + k - i,n-1);
				if (upper <= 0)
					sum += prefix_sum_cols[col+i][lower];
				else
					sum += prefix_sum_cols[col+i][lower] - prefix_sum_cols[col+i][upper-1];
			}
			for (int i = 1; i <= k && col - i >= 0; i++)
			{
				int upper = row - k + i;
				int lower = min(row + k - i, n - 1);
				if (upper <= 0)
					sum += prefix_sum_cols[col - i][lower];
				else
					sum += prefix_sum_cols[col - i][lower] - prefix_sum_cols[col-i][upper-1];
			}
			solution = max(solution, sum);
		}
	}
	cout << solution;
	return 0;
}