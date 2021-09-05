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
		ll solution; cin >> solution;
		for (int i = 0; i < n-1; i++)
		{
			ll a; cin >> a;
			solution &= a;
		}
		cout << solution << "\n";
	}
	return 0;
}