#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;

int main()
{
	freopen("cowqueue.in", "r", stdin);
	freopen("cowqueue.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n; cin >> n;
	vector<pair<int, int>> times(n);
	for (int i = 0; i < n; i++)
		cin >> times[i].first >> times[i].second;
	
	sort(times.begin(), times.end());
	int current_time = 0;
	for (int i = 0; i < n; i++)
	{
		if (current_time < times[i].first)
			current_time = times[i].first;
		current_time += times[i].second;
	}
	cout << current_time;
	return 0;
}