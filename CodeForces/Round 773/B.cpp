#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>
#include <string>
#include <map>
#include <set>
using namespace std;
typedef long long ll;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int test_cnt; cin >> test_cnt;
	while (test_cnt--)
	{
		int n; cin >> n;
		vector<ll> elements(n);
		for (int i = 0; i < n; i++)
			cin >> elements[i];
		
		sort(elements.begin(), elements.end());
		vector<ll> element_cnts;
		element_cnts.push_back(1);
		for (int i = 1; i < elements.size(); i++)
		{
			if (elements[i] == elements[i - 1])
				element_cnts.back()++;
			else
				element_cnts.push_back(1);
		}

		sort(element_cnts.begin(), element_cnts.end());
		int sol = element_cnts.size();
		for (int i = 0; i < n; i++)
		{
			if (i + 1 > element_cnts.size())
			{
				sol++;
			}

			cout << sol << " ";
		}
		cout << "\n";

	}
	return 0;
}