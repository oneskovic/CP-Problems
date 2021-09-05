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
		ll a, b; cin >> a >> b;
		ll diff = abs(a - b);
		if (a == 0 && b == 0)
		{
			cout << "0\n";
		}
		else if (diff == 0)
		{
			cout << "1\n";
		}
		else if (diff % 2 == 0)
		{
			cout << "2\n";
		}
		else
		{
			cout << "-1\n";
		}

	}

	return 0;
}
