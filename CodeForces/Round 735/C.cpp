#include <algorithm>
#include <iostream>
#include <vector>
#include <chrono>
#include <random>

using namespace std;
typedef long long ll;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int test_cnt; cin >> test_cnt;
	while (test_cnt--)
	{
		ll n, m; cin >> n >> m;
		ll mask = (ll)1 << 31;
		ll solution = 0;
		for (int i = 0; i < 31; i++)
		{
			bool n_has_1 = (bool)(n & mask);
			bool m_has_1 = (bool)(m & mask);
			if (n_has_1 && !m_has_1)
			{
				break;
			}
			if (m_has_1 && !n_has_1)
			{
				solution |= mask;
			}
			mask >>= 1;
		}
		cout << solution << "\n";
		
	}

	return 0;
}