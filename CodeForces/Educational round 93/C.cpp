#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <map>
using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	int test_cnt; cin >> test_cnt;
	while (test_cnt--)
	{
		int n; cin >> n;
		vector<int> elements(n);
		vector<int> pref_sum(n);
		vector<int> pref_0(n);
		string s; cin >> s;
		for (int i = 0; i < n; i++)
		{
			elements[i] = s[i] - '0';
		}
		if (elements[0] == 0)
			pref_0[0] = 1;
		
		else if (elements[0] > 1)
			pref_sum[0] = elements[0] - 1;
		
		for (int i = 1; i < n; i++)
		{
			pref_0[i] = pref_0[i - 1];
			pref_sum[i] = pref_sum[i - 1];
			if (elements[i] == 0)
				pref_0[i]++;
			else if (elements[i] > 1)
				pref_sum[i] += elements[i] - 1;
		}

		map<int,int> differences_left;
		long long solution = 0;
		for (int i = 0; i < n; i++)
		{
			int diff = pref_0[i] - pref_sum[i];
			solution += differences_left[diff];
			differences_left[diff]++;
			if (diff == 0)
			{
				solution++;
			}
		}
		cout << solution << "\n";
	}
	return 0;
}