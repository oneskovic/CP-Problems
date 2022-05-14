#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;

ll binpow(ll a, ll b) {
	ll res = 1;
	while (b > 0) {
		if (b & 1)
			res = res * a;
		a = a * a;
		b >>= 1;
	}
	return res;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int test_cnt; cin >> test_cnt;
	while (test_cnt--)
	{
		int n; cin >> n;
		ll count_zero = 0, count_one = 0;
		for (int i = 0; i < n; i++)
		{
			ll element; cin >> element;
			if (element == 0)
			{
				count_zero++;
			}
			else if (element == 1)
			{
				count_one++;
			}
		}
		ll result = count_one * binpow(2, count_zero);
		cout << result << "\n";
	}

	return 0;
}