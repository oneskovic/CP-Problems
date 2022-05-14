#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;
typedef long long ll;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	int test_cnt; cin >> test_cnt;
	while (test_cnt--)
	{
		int n; ll b, x, y; cin >> n >> b >> x >> y;

		ll sum = 0;
		ll current_element = 0;
		for (int i = 0; i < n; i++)
		{
			if (current_element+x <= b)
			{
				current_element += x;
			}
			else
			{
				current_element -= y;
			}
			sum += current_element;
		}
		cout << sum << "\n";

	}
	return 0;
}