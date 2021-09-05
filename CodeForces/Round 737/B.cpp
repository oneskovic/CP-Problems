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
		int n, k; cin >> n >> k;
		vector<pair<ll,int>> elements(n);
		for (int i = 0; i < n; i++)
		{
			cin >> elements[i].first;
			elements[i].second = i;
		}
		sort(elements.begin(), elements.end());
		int prev_added_pos = -2;
		int needed_sequences = 0;
		for (int i = 0; i < n; i++)
		{
			if (prev_added_pos+1 != elements[i].second)
			{
				needed_sequences++;
			}
			prev_added_pos = elements[i].second;
		}
		if (k >= needed_sequences)
		{
			cout << "Yes\n";
		}
		else
			cout << "No\n";
	}
	return 0;
}