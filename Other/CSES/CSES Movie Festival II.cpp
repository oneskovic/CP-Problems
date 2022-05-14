#include <algorithm>
#include <iostream>
#include <vector>
#include <set>
using namespace std;
typedef long long ll;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	int movie_cnt, member_cnt; cin >> movie_cnt >> member_cnt;
	vector<pair<ll, ll>> movie_end_start(movie_cnt);
	
	for (int i = 0; i < movie_cnt; i++)
		cin >> movie_end_start[i].second >> movie_end_start[i].first;
	
	sort(movie_end_start.begin(), movie_end_start.end());
	
	multiset<ll> member_finish_times;
	for (int i = 0; i < member_cnt; i++)
		member_finish_times.insert(0);

	int solution = 0;
	for (int i = 0; i < movie_cnt; i++)
	{
		ll current_start_time = movie_end_start[i].second;
		auto ub = member_finish_times.upper_bound(current_start_time);
		if (ub != member_finish_times.begin())
		{
			ub--;
			member_finish_times.erase(ub);
			member_finish_times.insert(movie_end_start[i].first);
			solution++;
		}
	}
	cout << solution << "\n";

	return 0;
}