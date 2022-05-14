#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>
#include <string>
#include <map>
#include <set>
using namespace std;
typedef long long ll;

ll solve(vector<ll> elements, ll x)
{
	int n = elements.size();
	map<ll, int> element_cnt;
	for (int i = 0; i < n; i++)
	{
		ll element = elements[i];
		element_cnt[element]++;
	}
	sort(elements.begin(), elements.end(), greater<ll>());
	ll sol = 0;
	for (int i = 0; i < n; i++)
	{
		if (element_cnt[elements[i]] == 0)
		{
			continue;
		}
		element_cnt[elements[i]]--;
		if (elements[i] % x == 0)
		{
			ll corresponding_element = elements[i] / x;
			if (element_cnt[corresponding_element] > 0)
			{
				element_cnt[corresponding_element]--;
			}
			else
			{
				sol++;
			}
		}
		else
			sol++;
	}
	return sol;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int test_cnt; cin >> test_cnt;
	while (test_cnt--)
	{
		int n; cin >> n;
		ll x; cin >> x;
		vector<ll> elements(n);
		for (int i = 0; i < n; i++)
		{
			cin >> elements[i];
		}
		
		cout << solve(elements,x) << "\n";
	}
	return 0;
}