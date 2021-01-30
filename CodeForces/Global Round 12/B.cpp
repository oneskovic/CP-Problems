#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;
#define ll long long

struct point
{
	int x, y;
};

int distance(const point& p1, const point& p2)
{
	return abs(p1.x - p2.x) + abs(p1.y - p2.y);
}

int main()
{
	int test_count; cin >> test_count;
	for (size_t test_no = 0; test_no < test_count; test_no++)
	{
		int n, k; cin >> n >> k;
		vector<point> points(n);
		vector<int> point_connection_count(n);
		for (size_t i = 0; i < n; i++)
			cin >> points[i].x >> points[i].y;
		
		for (size_t i = 0; i < n; i++)
		{
			for (size_t j = 0; j < n; j++)
			{
				if (i == j)
					continue;
				ll dist = distance(points[i], points[j]);
				if (dist <= k)
					point_connection_count[i]++;
			}
		}

		if (find(point_connection_count.begin(), point_connection_count.end(), n-1) != point_connection_count.end())
			cout << "1\n";
		else
			cout << "-1\n";
	}
	return 0;
}