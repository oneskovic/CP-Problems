#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;

struct point
{
	ll x, y;
};

ll dist(point a, point b)
{
	return abs(a.x - b.x) + abs(a.y - b.y);
}

ll shortest_path_through_points(point start, point a, point b)
{
	return dist(start, a) + dist(a, b) + dist(b, start);
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	int test_cnt; cin >> test_cnt;
	while (test_cnt--)
	{
		ll x, y, n, m;
		cin >> n >> m >> y >> x;
		point start = { x,y };
		vector<point> corners = { {1,1},{m,n},{1,n},{m,1} };
		pair<point, point> opt_corners;
		ll opt_dist = LLONG_MIN;
		for (int i = 0; i < 4; i++)
		{
			for (int j= 0; j < 4; j++)
			{
				ll d = shortest_path_through_points(start, corners[i], corners[j]);
				if (d >= opt_dist)
				{
					opt_dist = d;
					opt_corners = { corners[i], corners[j] };
				}
			}
		}
		cout << opt_corners.first.y << " " << opt_corners.first.x << " " << opt_corners.second.y << " " << opt_corners.second.x << "\n";
	}
	return 0;
}