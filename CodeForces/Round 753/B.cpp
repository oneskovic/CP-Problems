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
		ll x0, n; cin >> x0 >> n;
		ll offset = 0;
		if (n % 2 == 0)
		{
			ll k = n / 2;
			if (k % 2 == 0)
				offset = 0;
			else
				offset = 1;
		}
		else
		{
			ll k = (n-1) / 2;
			if (k % 2 == 0)
				offset = 0;
			else
				offset = 1;
			

			if (n % 4 == 0 || n % 4 == 1)
				offset -= n;
			else
				offset += n;
		}
		if (x0 % 2 != 0)
		{
			offset = -offset;
		}
		cout << x0 + offset << "\n";
	}
	return 0;
}