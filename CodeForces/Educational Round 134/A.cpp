#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
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
		string a, b; cin >> a >> b;
		set<char> s = { a[0],a[1],b[0],b[1] };
		cout << s.size() - 1 << "\n";
	}

	return 0;
}