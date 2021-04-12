#include <algorithm>
#include <iostream>
#include <vector>
#include <set>
#include <map>
using namespace std;
#define ll long long

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	
	int test_count; cin>>test_count;
	for (int test_no = 0; test_no < test_count; test_no++)
	{
		int n, k; cin >> n >> k;
		vector<ll> elements(n+2);
		for (size_t i = 1; i <= n; i++)
			cin >> elements[i];
		elements[0] = -1;
		elements.back() = (ll)1e9+1;
		sort(elements.begin(), elements.end());
		set<ll> distinct_elements(++elements.begin(), --elements.end());
		
		pair<ll, ll> first_space = { -1,-1 };
		for (size_t i = 0; i < elements.size() - 1; i++)
		{
			if (elements[i+1] - elements[i] > 1)
			{
				first_space = { elements[i],elements[i + 1] };
				break;
			}
		}

		if (k > 0 && first_space.second < elements.back())
		{
			ll max_el = elements[n];
			ll mex_el = first_space.first + 1;
			distinct_elements.insert((max_el + mex_el) / 2 + (max_el + mex_el) % 2);
			cout << distinct_elements.size() << "\n";
		}
		else
		{
			cout << n + k << "\n";
		}
	}
	return 0;
}
