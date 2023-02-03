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

	int n; cin >> n;
	vector<string> strings(n);
	for (int i = 0; i < n; i++)
		cin >> strings[i];
	sort(strings.begin(), strings.end());

	int query_cnt; cin >> query_cnt;
	while (query_cnt--)
	{
		string prefix; cin >> prefix;
		string search_ub = prefix + string(50,'z');

		int lb = lower_bound(strings.begin(), strings.end(), prefix) - strings.begin();
		int ub = upper_bound(strings.begin(), strings.end(), search_ub) - strings.begin();
		cout << ub - lb << "\n";
	}

	return 0;
}