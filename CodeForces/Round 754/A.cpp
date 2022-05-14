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
		ll a1, a2, a3;
		cin >> a1 >> a2 >> a3;
		ll val = a1 + a3 - 2 * a2;
		ll k = -val / 3;
		ll s1 = abs(val + (k+1) * 3);
		ll s2 = abs(val + (k-1) * 3);
		ll s3 = abs(val + k*3);
		cout << min(s1,min(s2,s3)) << "\n";
	}
	return 0;
}