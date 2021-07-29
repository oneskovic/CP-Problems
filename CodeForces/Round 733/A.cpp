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
		ll max_digit = 0;
		while (n > 0)
		{
			max_digit = max(max_digit, n % 10);
			n /= 10;
		}
		cout << max_digit << "\n";
	}
	return 0;
}