#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
#define ll long long

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	int test_count; cin >> test_count;
	for (size_t test_no = 0; test_no < test_count; test_no++)
	{
		int n; ll k;
		cin >> n >> k;
		bool possible = true;

		ll current_max;
		ll remaining = k-1;
		cin >> current_max;
		for (size_t i = 0; i < n-2; i++)
		{
			ll h; cin >> h;
			if (h > current_max)
			{
				ll diff = current_max - h;
				remaining -= diff;
				if (remaining < 0)
					possible = false;
			}
			remaining += k - 1;
		}
		ll last_h; cin >> last_h;
		ll diff = abs(last_h - current_max);		
	}
	return 0;
}