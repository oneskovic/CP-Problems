#include <algorithm>
#include <iostream>
#include <vector>
#include <iomanip>

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
		ll sum = 0;
		vector<ll> elements(n);
		for (int i = 0; i < n; i++)
		{
			cin >> elements[i];
			sum += elements[i];
		}
		sort(elements.begin(), elements.end());
		ll solution = elements.back();
		double rem = (double)(sum - elements.back()) / (n - 1);
		cout << fixed << setprecision(10) << (double)solution + rem << "\n";
	}
	return 0;
}