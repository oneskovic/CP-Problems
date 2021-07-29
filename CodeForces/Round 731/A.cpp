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
		int x_start, y_start, x_end, y_end, x_block, y_block;
		cin >> x_start >> y_start >> x_end >> y_end >> x_block >> y_block;
		int solution = abs(x_start - x_end) + abs(y_start - y_end);
		if (y_start == y_end && y_start == y_block)
		{
			int low = min(x_start, x_end), high = max(x_start, x_end);
			if (x_block >= low && x_block <= high)
			{
				solution += 2;
			}
		}
		else if (x_start == x_end && x_start == x_block)
		{
			int low = min(y_start, y_end), high = max(y_start, y_end);
			if (y_block >= low && y_block <= high)
			{
				solution += 2;
			}
		}
		cout << solution << "\n";
	}
	return 0;
}