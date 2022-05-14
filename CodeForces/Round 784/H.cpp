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
		int n, k; cin >> n >> k;
		vector<int> col_zeros_cnt(31);
		for (int i = 0; i < n; i++)
		{
			ll number; cin >> number;
			ll mask = 1;
			for (int j = 0; j <= 30; j++, mask <<= 1)
			{
				if ((number & mask) == 0)
				{
					col_zeros_cnt[j]++;
				}
			}
		}
		ll solution = 0;
		ll mask = (1 << 30);
		for (int col = 30; col >= 0; col--, mask >>= 1)
		{
			if (col_zeros_cnt[col] <= k)
			{
				solution += mask;
				k -= col_zeros_cnt[col];
			}
		}
		cout << solution << "\n";
	}

	return 0;
}
