#include <vector>
#include <iostream>
#include <algorithm>
#include <functional>

using namespace std;
#define ll long long
int main()
{
	ios::sync_with_stdio(false);
	int t; cin >> t;
	for (size_t test_no = 0; test_no < t; test_no++)
	{
		int n, k; cin >> n >> k;
		vector<ll> elements(n);
		for (size_t i = 0; i < n; i++)
			cin >> elements[i];
		sort(elements.begin(), elements.end(), greater<ll>());
		ll sum_to_add = 0;
		for (size_t i = 1; i <= k; i++)
			sum_to_add += elements[i];
		
		cout << sum_to_add + elements[0] << "\n";
	}
	return 0;
}