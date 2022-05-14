#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
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
		vector<ll> elements(n);
		for (int i = 0; i < n; i++)
			cin >> elements[i];

		ll sol = 0;
		for (int i = 0; i < n; i++)
		{
			ll mask = 1;
			for (int j = 0; j <= 31; j++)
			{
				if (elements[i] & mask)
				{
					sol |= mask;
				}
				mask <<= 1;
			}
		}

		cout << sol << "\n";
	}
	return 0;
}
