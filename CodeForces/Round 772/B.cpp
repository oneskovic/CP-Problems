#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <map>
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
		{
			cin >> elements[i];
		}
		vector<int> local_max_positions; local_max_positions.reserve(n);
		
		for (int i = 1; i < n-1; i++)
		{
			if (elements[i-1] < elements[i] && elements[i] > elements[i+1])
			{
				local_max_positions.push_back(i);
			}
		}

		int cnt_ops = 0;
		vector<bool> should_remove(local_max_positions.size(), true);
		for (int i = 0; i < local_max_positions.size(); i++)
		{
			int pos_current = local_max_positions[i];
			if (!(elements[pos_current-1] < elements[pos_current] && elements[pos_current] > elements[pos_current+1]))
			{
				should_remove[i] = false;
				continue;
			}
			if (pos_current+2 < elements.size())
			{
				should_remove[i] = false;
				elements[pos_current + 1] = max(elements[pos_current+2], elements[pos_current]);
				cnt_ops++;
			}
		}
		for (int i = 0; i < local_max_positions.size(); i++)
		{
			int pos = local_max_positions[i];
			if (should_remove[i])
			{
				elements[pos] = max(elements[pos - 1], elements[pos + 1]);
				cnt_ops++;
			}
		}
		cout << cnt_ops << "\n";
		for (int element: elements)
			cout << element << " ";
		cout << "\n";

	}


	return 0;
}
