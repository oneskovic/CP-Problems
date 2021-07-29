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
		int line_cnt, n, m; cin >> line_cnt >> n >> m;
		vector<int> actions1(n), actions2(m);
		for (int i = 0; i < n; i++)
			cin >> actions1[i];
		for (int i = 0; i < m; i++)
			cin >> actions2[i];
		int i = 0, j = 0;
		bool valid = true;
		vector<int> solution; solution.reserve(n + m);
		while ((i < n || j < m) && valid)
		{
			while (i < n && actions1[i] == 0)
			{
				solution.push_back(0);
				i++;
				line_cnt++;
			}
			while (j < m && actions2[j] == 0)
			{
				solution.push_back(0);
				j++;
				line_cnt++;
			}
			if (i == n && j == m)
			{
				break;
			}

			bool advanced = false;
			if (i < n && actions1[i] <= line_cnt)
			{
				solution.push_back(actions1[i++]);
				advanced = true;
			}
			if (j < m && actions2[j] <= line_cnt)
			{
				solution.push_back(actions2[j++]);
				advanced = true;
			}
			if (!advanced)
			{
				valid = false;
			}
		}
		if (!valid)
		{
			solution = { -1 };
		}

		for (int i : solution)
			cout << i << " ";
		cout << "\n";
	}
	return 0;
}