#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>
#include <unordered_map>
using namespace std;
#define ll long long
const ll mod = 1e9 + 7;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n; cin >> n;
	vector<ll> elements(n);
	for (size_t i = 0; i < n; i++)
		cin >> elements[i];
	
	unordered_map<ll, ll> subarray_count;
	stack<pair<int, int>> previous_elements;
	for (int i = 0; i < n; i++)
	{
		int current_element = elements[i];
		int count_left = 0;
		while (!previous_elements.empty() && current_element > elements[previous_elements.top().first])
		{
			count_left += previous_elements.top().second;
			count_left++;

			int previous_element = elements[previous_elements.top().first];
			ll total_subarrays = (previous_elements.top().second+1)%mod * (i - previous_elements.top().first);
			total_subarrays %= mod;
			subarray_count[previous_element] += total_subarrays;
			subarray_count[previous_element] %= mod;
			previous_elements.pop();
		}
		previous_elements.push({ i,count_left });
	}
	while (!previous_elements.empty())
	{
		int previous_element = elements[previous_elements.top().first];
		ll total_subarrays = (previous_elements.top().second + 1) % mod * (n - previous_elements.top().first);
		total_subarrays %= mod;
		subarray_count[previous_element] += total_subarrays;
		subarray_count[previous_element] %= mod;
		previous_elements.pop();
	}

	int query_count; cin >> query_count;
	for (size_t i = 0; i < query_count; i++)
	{
		int query; cin >> query;
		cout << subarray_count[query] << "\n";
	}
	return 0;
}