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
		vector<ll> elements(n);
		for (int i = 0; i < n; i++)
			cin >> elements[i];
		sort(elements.begin(), elements.end());
		ll max1 = elements[n - 1], max2 = elements[n - 2];
		ll min1 = elements[0], min2 = elements[1];
		
		cout << max1 + max2 - min1 - min2 << "\n";
	}
	return 0;
}