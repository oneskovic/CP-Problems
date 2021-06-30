#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;

void add_vertex(int parent, vector<vector<int>>& dp)
{
	vector<int> new_dp(21);
	new_dp[0] = parent;
	for (int i = 1; i <= 20; i++)
	{
		int index_at_half_dist = new_dp[i - 1];
		new_dp[i] = index_at_half_dist == -1 ? -1 : dp[index_at_half_dist][i - 1];
	}
	dp.push_back(new_dp);
}

int find_furthest_vertex(int vertex, const vector<ll>& gold_ammount, const vector<vector<int>>& dp)
{
	while (dp[vertex][0] > -1)
	{
		bool found = false;
		for (int i = 20; i >= 0 && !found; i--)
		{
			int vertex_at_dist = dp[vertex][i];
			if (vertex_at_dist > -1 && gold_ammount[vertex_at_dist] > 0)
			{
				vertex = vertex_at_dist;
				found = true;
			}
		}
		if (!found)
			return vertex;
	}
	return vertex;
}

void buy_gold(int vertex, ll ammount_to_buy, vector<ll>& gold_ammount, vector<ll>& gold_price, const vector<vector<int>>& dp)
{
	ll remaining_ammount = ammount_to_buy;
	ll bought_gold = 0;
	ll money_spent = 0;
	int furthest_vertex = find_furthest_vertex(vertex, gold_ammount, dp);
	while (gold_ammount[furthest_vertex] > 0 && remaining_ammount > 0)
	{
		ll to_buy = min(remaining_ammount, gold_ammount[furthest_vertex]);
		money_spent += to_buy * gold_price[furthest_vertex];
		gold_ammount[furthest_vertex] -= to_buy;
		remaining_ammount -= to_buy;
		bought_gold += to_buy;
		furthest_vertex = find_furthest_vertex(vertex, gold_ammount, dp);
	}
	cout << bought_gold << " " << money_spent << endl;
}

int main()
{
	vector<ll> gold_ammount, gold_price;
	int query_count; ll gold_ammount_root, gold_price_root;
	cin >> query_count >> gold_ammount_root >> gold_price_root;

	gold_ammount.push_back(gold_ammount_root);
	gold_price.push_back(gold_price_root);
	vector<vector<int>> dp;
	dp.push_back(vector<int>(21, -1));

	vector<int> vertex_index_map(query_count + 1);
	for (int query_index = 0; query_index < query_count; query_index++)
	{
		int query_type; cin >> query_type;
		if (query_type == 1)
		{
			int parent; cin >> parent;
			ll ammount, price;
			cin >> ammount >> price;
			gold_ammount.push_back(ammount);
			gold_price.push_back(price);
			parent = vertex_index_map[parent];
			add_vertex(parent, dp);
			vertex_index_map[query_index + 1] = gold_ammount.size() - 1;
		}
		else
		{
			int vertex; ll ammount;
			cin >> vertex >> ammount;
			vertex = vertex_index_map[vertex];
			buy_gold(vertex, ammount, gold_ammount, gold_price, dp);
		}
	}
	return 0;
}