#include <iostream>
#include <algorithm>
#include <vector>
#include <functional>
using namespace std;
#define ll long long

vector<ll> find_all_divisors(ll n)
{
	ll i = 1;
	vector<ll> divisors;
	while (i*i <= n)
	{
		if (n % i == 0)
		{
			divisors.push_back(i);
			if (i*i != n)
			{
				divisors.push_back(n / i);
			}
		}
		i++;
	}
	return divisors;
}

bool check(const vector<ll>& elements, ll segment_sum)
{
	ll current_sum = 0;
	for (size_t i = 0; i < elements.size(); i++)
	{
		if (elements[i] + current_sum > segment_sum)
		{
			return false;
		}
		else if (elements[i] + current_sum == segment_sum)
		{
			current_sum = 0;
		}
		else
		{
			current_sum += elements[i];
		}
	}
	return true;
}


int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	int test_count; cin >> test_count;
	for (size_t test_no = 0; test_no < test_count; test_no++)
	{
		int n; cin >> n;
		vector<ll> elements(n);
		ll sum = 0;
		for (size_t i = 0; i < n; i++)
		{
			cin >> elements[i];
			sum += elements[i];
		}
		vector<ll> all_divisors = find_all_divisors(sum);
		sort(all_divisors.begin(), all_divisors.end(),greater<ll>());

		int min_operations = -1;
		for (ll divisor: all_divisors)
		{
			ll sum_in_segment = sum / divisor;
			if (check(elements,sum_in_segment))
			{
				min_operations = n - divisor;
				break;
			}
		}
		cout << min_operations << "\n";
	}
	return 0;
}