#include <algorithm>
#include <iostream>
#include <vector>
#include <set>
using namespace std;
typedef long long ll;

vector<vector<int>> rotate_mat(const vector<vector<int>>& mat)
{
	int n = mat.size();
	auto rotated = vector<vector<int>>(n, vector<int>(n));
	for (int col = 0; col < n; col++)
	{
		for (int row = 0; row < n; row++)
		{
			rotated[col][n - row - 1] = mat[row][col];
		}
	}
	return rotated;
}

void print_mat(const vector<vector<int>>& mat)
{
	int n = mat.size();
	for (int row = 0; row < n; row++)
	{
		for (int col = 0; col < n; col++)
			cout << mat[row][col] << " ";
		cout << "\n";
	}
	cout << "\n";
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n, perimeter;
	cin >> n >> perimeter;
	vector<vector<int>> mat(n, vector<int>(n));
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			cin >> mat[i][j];
	
	print_mat(mat);
	auto r1 = rotate_mat(mat);
	print_mat(r1);
	auto r2 = rotate_mat(r1);
	print_mat(r2);
	auto r3 = rotate_mat(r2);
	print_mat(r3);
	auto r4 = rotate_mat(r3);
	print_mat(r4);


	return 0;
}