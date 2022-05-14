#include <algorithm>
#include <iostream>
#include <vector>
#include <limits.h>
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
		sort(elements.begin(), elements.end());
		ll delta = 0;
		ll maximal_minimum = LLONG_MIN;
		for (int i = 0; i < n; i++)
		{
			ll new_value = elements[i] + delta;
			maximal_minimum = max(maximal_minimum, new_value);
			delta -= new_value;
		}
		cout << maximal_minimum << "\n";
	}
	return 0;
}