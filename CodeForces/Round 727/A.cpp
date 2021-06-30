#include <algorithm>
#include <iostream>
#include <vector>
#include <math.h>
using namespace std;
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int test_cnt; cin >> test_cnt;
	while (test_cnt--)
	{
		long long n, x, t;
		cin >> n >> x >> t;
		if ((n-1)*x <= t)
		{
			long long a = n - 1;
			cout << a * (a + 1) / 2 << "\n";
		}
		else
		{
			long long k = ceil(n - 1 - (double)t / x);
			if (k <= n - 1 - (double)t / x)
			{
				k++;
			}
			long long sum = k * (t / x);
			long long a = n - k - 1;
			long long rem = a * (a + 1) / 2;
			cout << sum + rem << "\n";
		}
	}
	return 0;
}