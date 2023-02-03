#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
using namespace std;
typedef long long ll;

bool two_zeros_in_row(const vector<vector<bool>>& mat)
{
	int n = mat.size(), m = mat[0].size();
	for (int row = 0; row < n; row++)
		for (int col = 0; col < m-1; col++)
			if (mat[row][col] == 0 && mat[row][col] == mat[row][col+1])
				return 1;
	return 0;
}

bool two_zeros_in_col(const vector<vector<bool>>& mat)
{
	int n = mat.size(), m = mat[0].size();
	for (int col = 0; col < m; col++)
		for (int row = 0; row < n-1; row++)
			if (mat[row][col] == 0 && mat[row][col] == mat[row+1][col])
				return 1;
	return 0;
}

int min_erased_if_placed(const vector<vector<bool>>& mat, int row, int col)
{
	int cnt1 = mat[row][col] + mat[row + 1][col] + mat[row + 1][col + 1];
	int cnt2 = mat[row][col] + mat[row][col + 1] + mat[row + 1][col + 1];
	int cnt3 = mat[row][col] + mat[row][col + 1] + mat[row + 1][col];
	int cnt4 = mat[row + 1][col] + mat[row + 1][col + 1] + mat[row][col + 1];
	return min(min(cnt1, cnt2),min(cnt3,cnt4));
}

int min_erased_to_make_two_connected(const vector<vector<bool>>& mat)
{
	int n = mat.size(), m = mat[0].size();
	int result = 3;
	for (int row = 0; row < n-1; row++)
		for (int col = 0; col < m-1; col++)
			result = min(result, min_erased_if_placed(mat, row, col));
	return result;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	int test_cnt; cin >> test_cnt;
	while (test_cnt--)
	{
		int n, m; cin >> n >> m;
		vector<vector<bool>> mat(n, vector<bool>(m));
		int cnt_ones = 0;
		for (int i = 0; i < n; i++)
		{
			string s; cin >> s;
			for (int j = 0; j < m; j++)
			{
				mat[i][j] = s[j] == '1';
				cnt_ones += mat[i][j];
			}
		}
		if (two_zeros_in_col(mat) || two_zeros_in_row(mat))
		{
			cout << cnt_ones << "\n";
		}
		else
		{
			int t = min_erased_to_make_two_connected(mat);
			cout << cnt_ones - t + 1 << "\n";
		}
	}
	return 0;
}