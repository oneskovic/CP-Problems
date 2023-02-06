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

	int n; cin >> n;
	vector<int> a(n), b(n), c(n);
	for (int i = 0; i < n; i++)
		cin >> a[i];
	for (int i = 0; i < n; i++)
		cin >> b[i];
	for (int i = 0; i < n; i++)
	{
		cin >> c[i];
		c[i]--;
	}

	map<int, int> value_in_b_cnt;
	for (int i = 0; i < n; i++)
		value_in_b_cnt[b[c[i]]]++;
	
	ll solution = 0;
	for (int i = 0; i < n; i++)
	{
		int x = a[i];
		solution += value_in_b_cnt[x];
	}
	cout << solution;
	return 0;
}