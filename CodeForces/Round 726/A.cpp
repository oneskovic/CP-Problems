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
		int n; cin >> n;
		ll sum = 0;
		for (size_t i = 0; i < n; i++)
		{
			int a; cin >> a;
			sum += a;
		}
		if (sum < n)
		{
			cout << 1 << "\n";
		}
		else
		{
			cout << (sum - n) << "\n";
		}
	}
	return 0;
}