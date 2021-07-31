#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

typedef long long ll;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	int test_cnt; cin >> test_cnt;
	while (test_cnt--)
	{
		int n,p; cin >> n >> p;
		vector<pair<int,int>> elements(n);
		for (int i = 0; i < n; i++)
		{
			cin >> elements[i].first;
			elements[i].second = i;
		}
		auto elements_unsorted = elements;

		sort(elements.begin(), elements.end());
		vector<bool> connected(n);
		ll total_weight = 0;
		for (int pos_in_sorted = 0; pos_in_sorted < n; pos_in_sorted++)
		{
			int current_gcd = elements[pos_in_sorted].first;
			if (current_gcd >= p)
				break;
			
			int pos_of_element = elements[pos_in_sorted].second;
			
			for (int l = pos_of_element-1; l >= 0 && elements_unsorted[l].first % current_gcd == 0; l--)
			{
				if (connected[l])
					break;

				total_weight += current_gcd;
				connected[l] = true;
			}
			for (int r = pos_of_element+1; r < n && elements_unsorted[r].first % current_gcd == 0; r++)
			{
				if (connected[r-1])
					break;
				
				total_weight += current_gcd;
				connected[r-1] = true;
			}
		}

		for (int i = 0; i < n-1; i++)
			if (!connected[i])
				total_weight += p;
		cout << total_weight << "\n";
	}
	return 0;
}