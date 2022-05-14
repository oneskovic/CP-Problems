#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;

ll arithmetic_sum(ll a, ll b)
{
	return -(a - b - 1) * (a + b) / 2;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int test_cnt; cin >> test_cnt;
	while (test_cnt--)
	{
		int n; cin >> n;
		vector<ll> times(n);
		vector<ll> hp(n);
		for (int i = 0; i < n; i++)
		{
			cin >> times[i];
		}
		for (int i = 0; i < n; i++)
		{
			cin >> hp[i];
		}
		ll score = arithmetic_sum(1, hp[0]);
		for (int i = 1; i < n; i++)
		{
			ll delta_t = times[i] - times[i - 1];
			if (delta_t >= hp[i])
			{
				score += arithmetic_sum(1, hp[i]);
			}
			else
			{
				if (hp[i-1]+delta_t >= hp[i])
				{
					score += arithmetic_sum(hp[i - 1] + 1, hp[i - 1] + delta_t);
				}
				else
				{
					ll s = arithmetic_sum(1, hp[i]) - arithmetic_sum(1, hp[i - 1]);
					score += s;
				}
				hp[i] = max(hp[i], hp[i - 1] + delta_t);
			}
		}
		cout << score << "\n";
	}

	return 0;
}