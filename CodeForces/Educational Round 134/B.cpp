#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int test_cnt; cin >> test_cnt;
	while (test_cnt--)
	{
		int n, m; cin >> n >> m;
		int x, y; cin >> y >> x;
		int dist; cin >> dist;
		int smallest_x = x - dist; int largest_x = x + dist;
		int smallest_y = y - dist; int largest_y = y + dist;
		if ((smallest_x <= 1 && largest_x >= m) ||
			(smallest_y <= 1 && largest_y >= n) ||
			(smallest_y  <= 1 && smallest_x <= 1) ||
			(largest_y >= n && largest_x >= m))
			cout << "-1\n";
		else if (n - y + m - x <= dist || x + y - 2 <= dist)
			cout << "-1\n";
		else
			cout << n + m - 2 << "\n";
		
	}

	return 0;
}