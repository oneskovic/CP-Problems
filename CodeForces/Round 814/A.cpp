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
		ll n, m; cin >> n >> m;
		if (n % 2 == 1)
		{
			if (m % 2 == 1)
				cout << "Tonya\n";
			else
				cout << "Burenka\n";
		}
		else
		{
			if (m % 2 == 1)
				cout << "Burenka\n";
			else
				cout << "Tonya\n";
		}
	}

	return 0;
}