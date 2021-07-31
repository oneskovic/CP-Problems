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
		ll sum = 0;
		for (int i = 0; i < n; i++)
		{
			ll element; cin >> element;
			sum += element;
		}
		ll one_higher_cnt = sum % n;
		ll one_lower_cnt = n - one_higher_cnt;
		cout << one_higher_cnt*one_lower_cnt << "\n";
	}
	return 0;
}