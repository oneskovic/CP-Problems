#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);


	int n; ll k, x;
	cin >> n >> k >> x;
	vector<ll> elements(n);
	for (int i = 0; i < n; i++)
		cin >> elements[i];
	sort(elements.begin(), elements.end());
	vector<ll> costs;
	for (int i = 0; i < n-1; i++)
	{
		if (elements[i+1] - elements[i] > x)
		{
			costs.push_back((elements[i + 1] - elements[i]) / x);
			if ((elements[i + 1] - elements[i]) % x == 0)
			{
				costs.back()--;
			}
		}
	}
	ll group_cnt = costs.size() + 1;
	sort(costs.begin(), costs.end());
	int j = 0;
	while (j < costs.size() && costs[j] <= k)
	{
		k -= costs[j++];
		group_cnt--;
	}
	cout << group_cnt << "\n";
	
	return 0;
}