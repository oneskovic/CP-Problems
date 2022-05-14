#include <algorithm>
#include <iostream>
#include <vector>
#include <set>
#include <queue>
using namespace std;
typedef long long ll;

vector<int> topsort(const vector<vector<int>>& dag, const vector<int>& parent)
{
	vector<int> degree(dag.size());
	queue<int> deg_zero_nodes;
	for (int i = 0; i < dag.size(); i++)
	{
		if (dag[i].size() == 0)
			deg_zero_nodes.push(i);
		degree[i] = dag[i].size();
	}

	vector<int> solution; solution.reserve(dag.size());
	while (!deg_zero_nodes.empty())
	{
		int node = deg_zero_nodes.front();
		deg_zero_nodes.pop();
		solution.push_back(node);
		if (parent[node] != -1)
		{
			degree[parent[node]]--;
			if (degree[parent[node]] == 0)
				deg_zero_nodes.push(parent[node]);
		}
	}
	return solution;
}

ll merge_sets(set<ll>& larger_set, ll larger_set_delta, const set<ll>& smaller_set, ll smaller_set_delta)
{
	ll erased_cnt = 0;
	for (ll x: smaller_set)
	{
		ll real_time = x + smaller_set_delta;
		ll time_in_larger_set = real_time - larger_set_delta;
		if (larger_set.find(time_in_larger_set) != larger_set.end())
		{
			larger_set.erase(time_in_larger_set);
			erased_cnt += 2;
		}
		else
		{
			larger_set.insert(time_in_larger_set);
		}
	}
	return erased_cnt;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n, m; cin >> n >> m;
	vector<int> tree(n-1);
	vector<vector<int>> dag(n, vector<int>());
	vector<int> parent(n, -1);
	for (int i = 0; i < n - 1; i++)
	{
		cin >> tree[i];
		tree[i]--;
		dag[tree[i]].push_back(i+1);
		parent[i + 1] = tree[i];
	}

	vector<set<ll>*> times_in_node(n);
	for (int i = 0; i < n; i++)
	{
		times_in_node[i] = new set<ll>();
	}
	vector<ll> time_offsets(n, 0);

	ll solution = 0;
	for (int i = 0; i < m; i++)
	{
		ll time; int node;
		cin >> time >> node;
		node--;
		if (times_in_node[node]->find(time) != times_in_node[node]->end())
		{
			solution += 2;
			times_in_node[node]->erase(time);
		}
		else
			times_in_node[node]->insert(time);
	}

	auto sorted_nodes = topsort(dag, parent);
	for (int node: sorted_nodes)
	{
		set<ll>* merged_children_set = new set<ll>();
		ll merged_children_offset = 0;

		for (int child: dag[node])
		{
			if (times_in_node[child]->size() > merged_children_set->size())
			{
				solution += merge_sets(*times_in_node[child], time_offsets[child], *merged_children_set, merged_children_offset);
				merged_children_set = times_in_node[child];
				merged_children_offset = time_offsets[child];
			}
			else
			{
				solution += merge_sets(*merged_children_set, merged_children_offset, *times_in_node[child], time_offsets[child]);
			}
		}

		if (times_in_node[node]->size() > merged_children_set->size())
		{
			solution += merge_sets(*times_in_node[node], time_offsets[node], *merged_children_set, merged_children_offset+1);
		}
		else
		{
			solution += merge_sets(*merged_children_set, merged_children_offset, *times_in_node[node], time_offsets[node]-1);
			times_in_node[node] = merged_children_set;
			time_offsets[node] = merged_children_offset+1;
		}
	}
	cout << solution << "\n";

	return 0;
}