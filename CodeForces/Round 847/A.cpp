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
	string pi = "314159265358979323846264338327950288419716939937510";
	while (test_cnt--)
	{
		string s; cin >> s;
		int sol;
		for (sol = 0; sol < s.size(); sol++)
			if (s[sol] != pi[sol])
				break;
	
		cout << sol << "\n";
	}

	return 0;
}