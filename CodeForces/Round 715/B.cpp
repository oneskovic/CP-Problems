#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
using namespace std;
typedef long long ll;
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	int test_cnt; cin >> test_cnt;

	for (size_t test_no = 0; test_no < test_cnt; test_no++)
	{
		int n; cin >> n;
		string s; cin >> s;
		if (n % 3 != 0)
		{
			cout << "NO\n";
			continue;
		}

		int k = n / 3;
		vector<int> t_positions, m_positions;
		for (size_t i = 0; i < n; i++)
		{
			if (s[i] == 'T')
				t_positions.push_back(i);
			else
				m_positions.push_back(i);
		}
		if (t_positions.size() != 2*k)
		{
			cout << "NO\n";
			continue;
		}
		int t1 = 0, t2 = k;
		int m = 0;
		bool possible = true;
		while (t1 < k)
		{
			if (t_positions[t1] >= m_positions[m] || m_positions[m] >= t_positions[t2])
			{
				possible = false;
				break;
			}
			t1++;
			t2++;
			m++;
		}
		if (possible)
			cout << "YES\n";
		else
			cout << "NO\n";
	}
	return 0;
}