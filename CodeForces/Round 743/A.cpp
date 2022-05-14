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
	while (test_cnt--)
	{
		int n; cin >> n;
		string s; cin >> s;
		ll operations = s[n-1]-'0';
		for (int i = n-2; i >= 0; i--)
		{
			if (s[i] > '0')
			{
				operations++;
				operations += s[i] - '0';
			}
		}
		cout << operations << "\n";
	}

	return 0;
}
