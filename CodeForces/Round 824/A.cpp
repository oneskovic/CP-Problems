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
		ll n; cin >> n;
		n -= 4;
		if (n % 3 == 0 || n % 3 == 1)
		{
			cout << max((ll)0, n / 3 - 1) << "\n";
		}
		else
			cout << n / 3 << "\n";
	}

	return 0;
}