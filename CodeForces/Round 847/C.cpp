#include <algorithm>
#include <iostream>
#include <vector>
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
		vector<vector<int>> m(n, vector<int>(n-1));
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n-1; j++)	
				cin >> m[i][j];
		map<int, int> counts;
		map<int, int> time_appeared;
		for (int col = 0; col < n-1; col++)
		{
			for (int r = 0; r < n; r++)
			{
				int x = m[r][col];
				if (time_appeared.find(x) == time_appeared.end())
					time_appeared[x] = col;
				counts[x]++;
			}
			int x1 = counts.begin()->first;
			int x2 = (++counts.begin())->first;
			int to_print;
			if (counts[x1] == counts[x2])
				to_print = time_appeared[x1] < time_appeared[x2] ? x1 : x2;
			else
				to_print = counts[x1] > counts[x2] ? x1 : x2;
			counts.erase(to_print);
			cout << to_print << " ";
		}
		cout << counts.begin()->first;
		cout << endl;
	}

	return 0;
}