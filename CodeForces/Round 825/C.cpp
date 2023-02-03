#include <algorithm>
#include <iostream>
#include <vector>
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
		vector<int> v(n);
		vector<vector<int>> diff_map(n + 5, vector<int>());
		set<int> bad_positions;
		for (int i = 0; i < n; i++)
		{
			cin >> v[i];
			int d = v[i] - (i + 1);
			if (d < 0)
			{
				diff_map[-d].push_back(i);
				bad_positions.insert(i);
			}
		}
		
		ll solution = 0;
		int offset = 0;
		for (int i = 0; i < n; i++)
		{
			int r = n;
			if (!bad_positions.empty())
				r = *bad_positions.begin();
			solution += r - i;
			offset++;
			for (int pos: diff_map[offset])
				bad_positions.erase(pos);
			
		}
		cout << solution << "\n";
	}

	return 0;
}