#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;
typedef long long ll;

struct query
{
	int athlete_id;
	ll round_cnt;
};

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int test_cnt; cin >> test_cnt;
	while (test_cnt--)
	{
		int n, q; cin >> n >> q;
		deque<pair<int, int>> athletes;
		int max_strength = -1;
		for (int i = 0; i < n; i++)
		{
			int strength; cin >> strength;
			max_strength = max(max_strength, strength);
			athletes.push_back({ i+1,strength });
		}
		vector<pair<query, int>> queries(q);
		vector<ll> query_solutions(q);
		for (int i = 0; i < q; i++)
		{
			cin >> queries[i].first.athlete_id >> queries[i].first.round_cnt;
			queries[i].second = i;
		}
		sort(queries.begin(), queries.end(), [](const pair<query,int>& lhs, const pair<query,int>& rhs) {return lhs.first.round_cnt < rhs.first.round_cnt; });
		
		vector<int> wins_till_loop(n + 1);
		int current_query_id = 0;
		int current_round_number = 1;

		while (athletes.front().second < max_strength)
		{
			auto athlete1 = athletes.front();
			athletes.pop_front();
			auto athlete2 = athletes.front();
			athletes.pop_front();
			if (athlete1.second < athlete2.second)
				swap(athlete1, athlete2);
			
			wins_till_loop[athlete1.first]++;
			athletes.push_front(athlete1);
			athletes.push_back(athlete2);
			while (current_query_id < queries.size() && queries[current_query_id].first.round_cnt == current_round_number)
			{
				int query_id = queries[current_query_id].second;
				int athlete_id = queries[current_query_id].first.athlete_id;
				query_solutions[query_id] = wins_till_loop[athlete_id];
				current_query_id++;
			}
			current_round_number++;
		}
		int rounds_till_loop = current_round_number;
		while (current_query_id < queries.size())
		{
			while (current_query_id < queries.size() && queries[current_query_id].first.round_cnt == current_round_number)
			{
				int query_id = queries[current_query_id].second;
				int athlete_id = queries[current_query_id].first.athlete_id;
				if (athletes.front().first == athlete_id)
					query_solutions[query_id] = current_round_number - rounds_till_loop + 1 + wins_till_loop[athlete_id];
				else
					query_solutions[query_id] = wins_till_loop[athlete_id];
				current_query_id++;
			}
			if (current_query_id < queries.size())
				current_round_number = queries[current_query_id].first.round_cnt;
		}
		for (ll ans: query_solutions)
			cout << ans << "\n";
		
	}

	return 0;
}