#include <vector>
#include <iostream>
#include <algorithm>
#include <functional>
#define ll long long
using namespace std;

bool check(vector<int>& elements)
{
	ll sum = 0, element_at_zero = elements[0];
	size_t position_when_zero = 0;
	bool possible = true;
	bool just_started = true;

	for (size_t i = 0; i < elements.size(); i++)
	{
		if (sum == 0 && !just_started)
		{
			if (elements[i] != element_at_zero && elements[i] != 0)
			{
				swap(elements[i], elements[position_when_zero]);
				possible = true;
				break;
			}
		}
		else
		{
			sum += elements[i];
			just_started = false;
			if (sum == 0)
			{
				possible = false;
				element_at_zero = elements[i];
				position_when_zero = i;
			}
		}
	}
	return possible;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int t; cin >> t;
	for (size_t test_no = 0; test_no < t; test_no++)
	{
		int n; cin >> n;
		vector<int> elements; elements.reserve(n);
		ll zeros_count = 0;
		for (size_t i = 0; i < n; i++)
		{
			int element; cin >> element;
			if (element == 0)
				zeros_count++;
			else
				elements.push_back(element);
		}
		sort(elements.begin(), elements.end(), greater<ll>());
		for (size_t i = 0; i < zeros_count; i++)
			elements.push_back(0);

		bool possible = check(elements);
		if (!possible)
		{
			reverse(elements.begin(), elements.begin()+n-zeros_count);
			possible = check(elements);
		}

		if (possible)
		{
			cout << "YES\n";
			for (size_t i = 0; i < n; i++)
				cout << elements[i] << " ";
			cout << "\n";
		}
		else
			cout << "NO\n";
	}
	return 0;
}