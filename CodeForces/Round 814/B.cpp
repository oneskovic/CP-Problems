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
		ll n, k; cin >> n >> k;
		if (k % 4 == 0)
			cout << "NO\n";
		else if (k % 4 == 1 || k % 4 == 3)
		{
			cout << "YES\n";
			for (int i = 1; i <= n; i+=2)
				cout << i << " " << i + 1 << "\n";
		}
		else
		{
			cout << "YES\n";
			int counter1 = 2, counter2 = 1;
			while (counter1 <= n)
			{
				cout << counter1 << " " << counter2 << "\n";
				counter1 += 4; counter2 += 2;
			}
			counter1 = 4;
			while (counter1 <= n)
			{
				cout << counter2 << " " << counter1 << "\n";
				counter1 += 4; counter2 += 2;
			}
		}
	}

	return 0;
}