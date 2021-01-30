#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
using namespace std;
#define ll long long

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	int test_count; cin >> test_count;
	for (size_t test_no = 0; test_no < test_count; test_no++)
	{
		int n; cin >> n;
		ll sum_all_values = 0;
		vector<ll> values(n+1);
		vector<ll> degree(n+1);
		for (size_t i = 1; i <= n; i++)
		{
			cin >> values[i];
			sum_all_values += values[i];
		}

		for (size_t i = 0; i < n - 1; i++)
		{
			int a, b; cin >> a >> b;
			degree[a]++;
			degree[b]++;
		}

		vector<ll> v;
		for (int i = 1; i <= n; i++)
			for (size_t j = 0; j < degree[i]-1; j++)
				v.push_back(values[i]);

		sort(v.begin(), v.end(), greater<ll>());
		ll solution = sum_all_values;
		cout << solution << " ";		
		int i = 0;
		for (size_t k = 0; k < n-2; k++)
		{
			solution += v[i++];
			cout << solution << " ";
		}
		cout << "\n";
	}

	return 0;
}