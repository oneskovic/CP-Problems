
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;

struct unit
{
	ll cost, score;
};

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n, max_cost; cin >> n >> max_cost;
	vector<unit> units(max_cost + 1, { LLONG_MAX,-1 });
	for (int i = 0; i < n; i++)
	{
		int cost; ll damage, health;
		cin >> cost >> damage >> health;
		ll score = damage * health;
		if (cost <= max_cost && units[cost].score <= score)
		{
			units[cost] = { cost, score };
		}
	}
	vector<ll> best_score_for_price(max_cost + 1);
	for (int price = 1; price < units.size(); price++)
	{
		ll score = units[price].score;
		for (int i = price, j = 1; i <= max_cost; i += price, j++)
		{
			best_score_for_price[i] = max(best_score_for_price[i], score * j);
		}
	}
	vector<ll> prefix_best_score(max_cost + 1);
	prefix_best_score[0] = best_score_for_price[0];
	for (int i = 1; i <= max_cost; i++)
		prefix_best_score[i] = max(prefix_best_score[i - 1], best_score_for_price[i]);

	int m; cin >> m;
	for (int i = 0; i < m; i++)
	{
		ll damage, health; cin >> damage >> health;
		auto lb = upper_bound(prefix_best_score.begin(), prefix_best_score.end(), damage * health);
		if (lb == prefix_best_score.end())
			cout << "-1\n";
		else
			cout << (lb - prefix_best_score.begin()) << "\n";
	}

	return 0;
}