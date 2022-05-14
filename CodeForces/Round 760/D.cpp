#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <set>

using namespace std;
typedef long long ll;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int test_cnt; cin >> test_cnt;
	while (test_cnt--)
	{
		int n, k; cin >> n >> k;
		vector<ll> elements(n);
		for (int i = 0; i < n; i++)
		{
			cin >> elements[i];
		}
		sort(elements.begin(), elements.end());
		ll score = 0;
		for (int i = 0; i < n-2*k; i++)
		{
			score += elements[i];
		}
		if (k > 0)
		{
			multiset<ll> s;
			for (int i = n-2*k; i < n; i++)
			{
				s.insert(elements[i]);
			}
			for (int i = 0; i < k; i++)
			{

			}
		}

		cout << score << "\n";
	}
	return 0;
}
