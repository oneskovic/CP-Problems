#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
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
		vector<ll> v(n);
		ll min_val = LLONG_MAX;
		for (int i = 0; i < n; i++)
		{
			cin >> v[i];
			min_val = min(min_val, v[i]);
		}
		if (v[0] == min_val)
			cout << "bob\n";
		else
			cout << "alice\n";
	}

	return 0;
}