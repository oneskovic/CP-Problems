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
		ll max_val = -1;
		ll solution = 0;
		for (int i = 0; i < n; i++)
		{
			ll element; cin >> element;
			solution += max((ll)0, element - (i+1) - solution);
		}
		cout << solution << "\n";
	}
	return 0;
}