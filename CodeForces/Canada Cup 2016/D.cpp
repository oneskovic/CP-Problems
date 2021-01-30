#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <queue>
using namespace std;
#define ll long long

struct team
{
	ll balloons, weight;
};

class compare_team
{
public:
	bool operator() (const team& lhs, const team& rhs)
	{
		return (lhs.weight - lhs.balloons) > (rhs.weight - rhs.balloons);
	}
};

bool operator<(const team& lhs, const team& rhs)
{
	return lhs.balloons < rhs.balloons;
}

bool operator>(const team& lhs, const team& rhs)
{
	return lhs.balloons > rhs.balloons;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n; cin >> n;
	ll available_balloons, a;
	cin >> available_balloons >> a;
	
	map<ll, ll> better_teams, worse_teams;
	for (size_t i = 0; i < n-1; i++)
	{
		team t;
		cin >> t.balloons >> t.weight;
		if (t.balloons > available_balloons)
			better_teams[t.balloons] += t.weight - t.balloons + 1;
		else
			worse_teams[t.balloons] += t.weight - t.balloons + 1;
	}

	multiset<ll> to_remove_better;
	for (auto kvp: better_teams)
		to_remove_better.insert(kvp.second);
	
	int best_place = to_remove_better.size() + 1;
	while (available_balloons > 0)
	{
		available_balloons -= *to_remove_better.begin();
		if (available_balloons >= 0)
		{
			to_remove_better.erase(to_remove_better.begin());
			while (!worse_teams.empty() && (--worse_teams.end())->first > available_balloons)
			{
				to_remove_better.insert((--worse_teams.end())->second);
				worse_teams.erase(--worse_teams.end());
			}
			int current_place = to_remove_better.size() + 1;
			best_place = min(current_place, best_place);
		}
		else
			break;
	}
	
	cout << best_place;
	return 0;
}
