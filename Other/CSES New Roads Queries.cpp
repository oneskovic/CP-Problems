#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>
#include <set>
using namespace std;

class DSU
{
public:
	DSU(int max_cnt);
	int find_set(int element);
	void join_sets(int element1, int element2);
	int size_of_set(int element);
private:
	vector<int> representative;
	vector<vector<int>> elements_in_set;
	vector<vector<int>> queries_in_set;
};
vector<pair<int, int>> queries;
vector<int> query_answers;
int current_time = 1;

vector<int> solve(int node_cnt, vector<pair<int, int>> edges)
{
	int edge_cnt = edges.size();
	int query_cnt = queries.size();
	for (int i = 0; i < edge_cnt; i++)
	{
		edges[i].first--;
		edges[i].second--;
	}
	query_answers = vector<int>(query_cnt, -1);
	DSU dsu(node_cnt);
	for (auto e : edges)
	{
		dsu.join_sets(e.first, e.second);
		current_time++;
	}
	return query_answers;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	int node_cnt, edge_cnt, query_cnt; cin >> node_cnt >> edge_cnt >> query_cnt;
	vector<pair<int, int>> edges(edge_cnt);
	for (int i = 0; i < edge_cnt; i++)
		cin >> edges[i].first >> edges[i].second;
	
	queries = vector<pair<int, int>>(query_cnt);
	query_answers = vector<int>(query_cnt, -1);
	for (int i = 0; i < query_cnt; i++)
	{
		cin >> queries[i].first >> queries[i].second;
		queries[i].first--;
		queries[i].second--;
	}
	auto solution = solve(node_cnt, edges);
	for (int i: solution)
		cout << i << "\n";
	
	return 0;
}

DSU::DSU(int max_cnt)
{
	representative = vector<int>(max_cnt);
	iota(representative.begin(), representative.end(), 0);
	elements_in_set = vector<vector<int>>(max_cnt, vector<int>());
	for (int i = 0; i < max_cnt; i++)
		elements_in_set[i].push_back(i);
	queries_in_set = vector<vector<int>>(max_cnt, vector<int>());
	for (int i = 0; i < queries.size(); i++)
	{
		int a = queries[i].first, b = queries[i].second;
		if (a == b)
		{
			query_answers[i] = 0;
			continue;
		}
		queries_in_set[a].push_back(i);
		queries_in_set[b].push_back(i);
	}
}

int DSU::find_set(int element)
{
	return representative[element];
}

void DSU::join_sets(int element1, int element2)
{
	int set1 = find_set(element1), set2 = find_set(element2);
	if (set1 == set2)
	{
		return;
	}
	if (size_of_set(set2) > size_of_set(set1))
	{
		swap(set1, set2);
	}
	// size[set2] <= size[set1]
	for (int i : elements_in_set[set2])
	{
		elements_in_set[set1].push_back(i);
		representative[i] = set1;
	}
	for (int query_index : queries_in_set[set2])
	{
		int a = queries[query_index].first, b = queries[query_index].second;
		if (find_set(a) == find_set(b))
		{
			if (query_answers[query_index] == -1)
			{
				query_answers[query_index] = current_time;
			}
		}
		else
		{
			queries_in_set[set1].push_back(query_index);
		}
	}
}

int DSU::size_of_set(int element)
{
	return elements_in_set[find_set(element)].size() + queries_in_set[find_set(element)].size();
}

