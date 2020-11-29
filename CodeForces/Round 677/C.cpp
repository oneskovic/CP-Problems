#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;
#define ll long long
int main()
{
	ios::sync_with_stdio(false);

	int test_count; cin >> test_count;
	for (size_t test_no = 0; test_no < test_count; test_no++)
	{
		int n; cin >> n;
		vector<ll> elements(n);
		for (size_t i = 0; i < n; i++)
			cin >> elements[i];
		
		if (all_of(elements.begin(), elements.end(), [elements](int a) {return a == elements[0]; }))
		{
			cout << "-1\n";
		}
		else
		{
			ll max_elem = *max_element(elements.begin(), elements.end());
			for (size_t i = 0; i < n; i++)
			{
				if (elements[i] == max_elem)
				{
					if (i > 0 && elements[i - 1] < max_elem)
					{
						cout << i + 1 << "\n";
						break;
					}
					else if (i < n-1 && elements[i+1] < max_elem)
					{
						cout << i + 1 << "\n";
						break;
					}

				}
			}
		}
	}
	return 0;
}