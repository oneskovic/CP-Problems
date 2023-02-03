#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n, k; cin >> n >> k;
	vector<int> to_add(n+1);
	for (int i = 0; i < k; i++)
	{
		int a, b; cin >> a >> b;
		a--;
		to_add[a]++;
		to_add[b]--;
	}
	vector<int> values(n);
	int sum = 0;
	for (int i = 0; i < n; i++)
	{
		sum += to_add[i];
		values[i] = sum;
	}
	sort(values.begin(), values.end());
	cout << values[n / 2];

	return 0;
}