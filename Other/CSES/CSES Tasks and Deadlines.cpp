#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n; cin >> n;
	vector<pair<ll,ll>> duration_deadline(n);
	for (int i = 0; i < n; i++)
		cin >> duration_deadline[i].first >> duration_deadline[i].second;
	sort(duration_deadline.begin(), duration_deadline.end());
	ll elapsed_time = 0;
	ll score = 0;
	for (int i = 0; i < n; i++)
	{
		elapsed_time += duration_deadline[i].first;
		score += duration_deadline[i].second - elapsed_time;
	}
	cout << score << "\n";

	return 0;
}