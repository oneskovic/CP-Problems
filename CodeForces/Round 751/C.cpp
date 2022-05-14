#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;

vector<ll> get_all_divisors(ll x)
{
	vector<ll> divisors = { 1 };
	if (x != 1)
		divisors.push_back(x);
	
	ll candidate = 2;
	while (candidate*candidate <= x)
	{
		if (x % candidate == 0)
		{
			divisors.push_back(candidate);
			if (x/candidate != candidate)
			{
				divisors.push_back(x / candidate);
			}
		}
		candidate++;
	}
	sort(divisors.begin(), divisors.end());
	return divisors;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	
	int test_cnt; cin >> test_cnt;
	while (test_cnt--)
	{
		int n; cin >> n;
		vector<ll> count_ones_per_col(31);
		for (int i = 0; i < n; i++)
		{
			ll number; cin >> number;
			ll mask = 1;
			for (int i = 0; i < 31; i++)
			{
				if (number & mask)
					count_ones_per_col[i]++;
				mask <<= 1;
			}
		}
		vector<vector<ll>> divisor_sets; divisor_sets.reserve(30);
		for (int i = 0; i < 31; i++)
		{
			if (count_ones_per_col[i] > 0)
			{
				divisor_sets.push_back(get_all_divisors(count_ones_per_col[i]));
			}
		}
		if (divisor_sets.empty())
		{
			for (int i = 1; i <= n; i++)
			{
				cout << i << " ";
			}
			cout << "\n";
		}
		else
		{
			vector<ll> intersection = divisor_sets[0];
			for (int i = 1; i < divisor_sets.size(); i++)
			{
				vector<ll> set_b = divisor_sets[i];
				vector<ll> new_intersection(intersection.size() + set_b.size());
				auto it = set_intersection(intersection.begin(), intersection.end(), set_b.begin(), set_b.end(), new_intersection.begin());
				new_intersection.resize(it - new_intersection.begin());
				intersection = new_intersection;
			}
			for (ll x: intersection)
			{
				cout << x << " ";
			}
			cout << "\n";
		}
	}

	return 0;
}