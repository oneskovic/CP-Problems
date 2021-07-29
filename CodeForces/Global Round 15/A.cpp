#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
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
		string s; cin >> s;
		string sorted_s = s;
		sort(sorted_s.begin(), sorted_s.end());
		int solution = 0;
		for (int i = 0; i < n; i++)
		{
			if (sorted_s[i] != s[i])
			{
				solution++;
			}
		}
		cout << solution << "\n";
	}

	return 0;
}