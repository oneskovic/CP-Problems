#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;

bool check(const vector<ll>& attack_times, ll strength, ll hp)
{
	for (int i = 1; i < attack_times.size(); i++)
	{
		ll duration = min(attack_times[i] - attack_times[i - 1], strength);
		hp -= duration;
	}
	hp -= strength;
	return hp <= 0;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int test_cnt; cin >> test_cnt;
	while (test_cnt--)
	{
		int n; cin >> n;
		ll hp; cin >> hp;
		vector<ll> attack_times(n);
		for (int i = 0; i < n; i++)
			cin >> attack_times[i];
		
		ll l = 0, r = hp + 10;
		while (r - l > 1)
		{
			ll mid = l + (r - l) / 2;
			if (check(attack_times,mid,hp))
				r = mid;
			else
				l = mid;
		}
		cout << r << "\n";
		
	}

	return 0;
}