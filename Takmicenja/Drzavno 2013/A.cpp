#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>
#include <string>
#include <set>
#include <map>
using namespace std;
typedef long long ll;

class PrefixArray2D
{
public:
	PrefixArray2D(const vector<vector<int>>& mat);
	int query_sum(int row, int col, int width, int height);
private:
	vector<vector<int>> prefix;
};

struct query
{
	int type;
	int row, col;
};
struct point
{
	int row, col;
};

point find_point_with_dist_equal(point p, int d, const vector<vector<int>>& mat)
{
	int n = mat.size();
	int m = mat[0].size();
	int l = max(0, p.col - d);
	int r = min(p.col + d, m-1);
	int u = max(0, p.row - d);
	int down = min(p.row + d, n - 1);
	for (int row = u; row <= d; row++)
	{
		if (mat[row][l] == 1)
		{
			return { row,l };
		}
		if (mat[row][r] == 1)
		{
			return { row,r };
		}
	}
	for (int col = l; col <= r; col++)
	{
		if (mat[u][col] == 1)
		{
			return { u,col };
		}
		if (mat[down][col] == 1)
		{
			return { down,col };
		}
	}
	return { -1,-1 };
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n, m; cin >> n >> m;
	vector<vector<int>> mat(n, vector<int>(m));
	for (int i = 0; i < n; i++)
	{
		string s; cin >> s;
		for (int j = 0; j < m; j++)
		{
			mat[i][j] = (s[j] == '1');
		}
	}

	auto prefix_mat = PrefixArray2D(mat);
	vector<vector<int>> cnt_points_with_distance;
	vector<point> query_points;
	
	int query_cnt; cin >> query_cnt;
	vector<query> queries;
	for (int i = 0; i < query_cnt; i++)
	{
		int type, row, col; cin >> type >> row >> col;
		row--; col--;
		queries.push_back({ type,row,col });
		if(type == 3)
		{
			cnt_points_with_distance.push_back(vector<int>(n));
			query_points.push_back({ row,col });
			for (int d = 0; d < n;d++)
			{
				cnt_points_with_distance.back()[d] = prefix_mat.query_sum(row - d, col - d, 2*d, 2*d);
			}
			int prefix = cnt_points_with_distance.back()[0];
			for (int d = 1; d < n; d++)
			{
				cnt_points_with_distance.back()[d] -= prefix;
				prefix += cnt_points_with_distance.back()[d];
			}
		}
	}
	int query_point_cnt = 0;
	for (auto query: queries)
	{
		if (query.type == 1)
		{
			mat[query.row][query.col] = 1;
			for (int i = query_point_cnt; i < query_points.size(); i++)
			{
				int d = max(abs(query.row - query_points[i].row), abs(query.col - query_points[i].col));
				cnt_points_with_distance[i][d]++;
			}
		}
		else if (query.type == 2)
		{
			mat[query.row][query.col] = 0;
			for (int i = 0; i < query_points.size(); i++)
			{
				int d = max(abs(query.row - query_points[i].row), abs(query.col - query_points[i].col));
				cnt_points_with_distance[i][d]--;
			}
		}
		else
		{
			int min_dist = -1;
			for (int d = 0; d < n; d++)
			{
				if (cnt_points_with_distance[query_point_cnt][d] > 0)
				{
					min_dist = d;
					break;
				}
			}
			if (min_dist == -1)
			{
				cout << "-1\n";
				continue;
			}
			auto p = find_point_with_dist_equal(query_points[query_point_cnt], min_dist, mat);
			cout << p.row + 1 << " " << p.col + 1 << "\n";
			query_point_cnt++;
		}
	}


	return 0;
}

PrefixArray2D::PrefixArray2D(const vector<vector<int>>& mat)
{
	int n = mat.size();
	int m = mat[0].size();
	prefix = vector<vector<int>>(n, vector<int>(m));
	prefix[0][0] = mat[0][0];
	for (int col = 1; col < m; col++)
		prefix[0][col] = prefix[0][col - 1] + mat[0][col];
	for (int row = 1; row < n; row++)
		prefix[row][0] = prefix[row - 1][0] + mat[row][0];

	for (int i = 1; i < n; i++)
	{
		for (int j = 1; j < m; j++)
		{
			int s1 = prefix[i][j - 1];
			int s2 = prefix[j][i - 1];
			int overlap = prefix[i - 1][j - 1];
			prefix[i][j] = s1 - overlap + s2 + mat[i][j];
		}
	}
}

int PrefixArray2D::query_sum(int row_top_left, int col_top_left, int width, int height)
{
	int n = prefix.size();
	int m = prefix[0].size();
	int row_bottom_right = row_top_left + width;
	int col_bottom_right = col_top_left + height;
	row_bottom_right = min(row_bottom_right, n-1);
	col_bottom_right = min(col_bottom_right, m-1);
	row_top_left = max(0, row_top_left);
	col_top_left = max(0, col_top_left);

	int s = prefix[row_bottom_right][col_bottom_right];
	int m1 = col_top_left > 0 ? prefix[row_bottom_right][col_top_left-1] : 0;
	int m2 = row_top_left > 0 ? prefix[row_top_left-1][col_bottom_right] : 0;
	int overlap = col_top_left > 0 && row_top_left > 0 ? prefix[row_top_left - 1][col_top_left - 1] : 0;

	return s - m1 - m2 + overlap;
}
