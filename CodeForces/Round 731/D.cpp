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
		ll prev_element = elements[0];
		cout << 0 << " ";
		for (int i = 1; i < n; i++)
		{
			ll current_element = 0;
			for (ll mask = 1; mask <= ((ll)1<<30); mask <<= 1)
			{
				bool must_have1 = (prev_element & mask);
				bool current_element_has1 = (elements[i] & mask);
				if (must_have1 && !current_element_has1)
				{
					current_element |= mask;
				}
			}
			cout << current_element << " ";
			prev_element = current_element ^ elements[i];
		}
		cout << "\n";
	}
	return 0;
}