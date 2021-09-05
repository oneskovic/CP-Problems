#include <algorithm>
#include <iostream>
#include <vector>
#include <stack>

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
		vector<ll> sorted;
		ll max_res = LLONG_MIN;
		for (int i = 0; i < n; i++)
		{
			if (!sorted.empty())
			{
				max_res = max(max_res, sorted.back() * elements[i]);
			}
			while (!sorted.empty() && elements[i] < sorted.back())
			{
				sorted.pop_back();
			}
			sorted.push_back(elements[i]);
			if (sorted.size() >= 2)
			{
				max_res = max(max_res, sorted[sorted.size()-1] * sorted[sorted.size() - 2]);
			}
		}
		cout << max_res << "\n";
	}

	return 0;
}