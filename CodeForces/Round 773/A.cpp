#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>
#include <string>
#include <map>
#include <set>
using namespace std;
typedef long long ll;

struct point
{
	ll x, y;
};

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int test_cnt; cin >> test_cnt;
	while (test_cnt--)
	{
		vector<point> points(3);
		for (int i = 0; i < 3; i++)
			cin >> points[i].x >> points[i].y;

		// Check if two points have the same y
		point other_point;
		bool two_have_same_y = false;
		ll same_y_value = -1;
		ll dx_same_y = 0;
		for (int i = 0; i < 3; i++)
		{
			for (int j = i+1; j < 3; j++)
			{
				if (points[i].y == points[j].y)
				{
					dx_same_y = abs(points[i].x - points[j].x);
					same_y_value = points[i].y;
					two_have_same_y = true;
					for (int k = 0; k < 3; k++)
					{
						if (points[k].y != points[i].y)
						{
							other_point = points[k];
						}
					}
				}
			}
		}
		ll sol = 0;
		if (two_have_same_y && other_point.y < same_y_value)
		{
			sol = dx_same_y;
		}

		cout << sol << "\n";
	}
	return 0;
}