#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>
#include <chrono>
#include <set>
using namespace std;
typedef long long ll;

int evaluate(const vector<int>& assignments, const vector<int>& v)
{
	int score = 0;
	for (int i = 0; i < assignments.size(); i++)
	{
		if (assignments[i] == v[i])
		{
			score++;
		}
	}
	return score;
}

vector<int> brutus(vector<int> v)
{
	vector<int> assignments(v.size());
	iota(assignments.begin(), assignments.end(), 1);
	int best_score = -1;
	vector<int> best_assignment;
	do
	{
		int score = evaluate(assignments, v);
		if (score > best_score)
		{
			best_assignment = assignments;
			best_score = score;
		}
	} while (next_permutation(assignments.begin(),assignments.end()));
	return best_assignment;
}

vector<int> generate_test()
{
	int n = rand() % 8;
	vector<int> v(n);
	for (int i = 0; i < v.size(); i++)
	{
		v[i] = rand() % n + 1;
	}
	return v;
}

vector<int> solve(const vector<int>& v)
{
	int n = v.size();
	vector<vector<int>> inverse_graph(n+1, vector<int>());
	for (int i = 0; i < v.size(); i++)
	{
		inverse_graph[v[i]].push_back(i + 1);
	}
	vector<int> outdegree(n + 1, 1), indegree(n + 1);
	for (int i = 1; i <= n; i++)
	{
		indegree[i] = inverse_graph[i].size();
	}

	vector<int> solution(n);
	for (int i = 1; i <= n; i++)
	{
		if (outdegree[i] == 1)
		{
			indegree[v[i - 1]] = 1;
			solution[i - 1] = v[i - 1];
			for (int node: inverse_graph[v[i-1]])
			{
				if (node != i)
				{
					outdegree[node] = 0;
				}
			}
		}
	}
	set<int> indeg0, outdeg0;
	for (int i = 1; i <= n; i++)
	{
		if (indegree[i] == 0)
		{
			indeg0.insert(i);
		}
		if (outdegree[i] == 0)
		{
			outdeg0.insert(i);
		}
	}
	vector<int> remaining_outdeg0;
	for(auto i = outdeg0.begin(); i != outdeg0.end(); i++)
	{
		if (outdeg0.size() == 1 && *indeg0.begin() == *outdeg0.begin())
		{
			int current_node = *outdeg0.begin();
			int node_to_disconnect = -1;
			for (int j = 0; j < solution.size(); j++)
			{
				if (solution[j] == v[current_node-1])
				{
					node_to_disconnect = j + 1;
					break;
				}
			}
			solution[node_to_disconnect-1] = *indeg0.begin();
			solution[current_node - 1] = v[current_node - 1];
			break;
		}
		int value = *i;
		auto indeg0_it = indeg0.find(value);
		if (indeg0_it != indeg0.end())
		{
			auto other_it = indeg0_it;
			other_it++;
			if (other_it == indeg0.end())
			{
				other_it = indeg0_it;
				other_it--;
			}
			solution[value - 1] = *other_it;
			indeg0.erase(other_it);
		}
		else
			remaining_outdeg0.push_back(value);
	}
	vector<int> remaining_indeg0(indeg0.begin(), indeg0.end());
	for (int i = 0; i < remaining_outdeg0.size(); i++)
	{
		int value = remaining_outdeg0[i];
		solution[value-1] = remaining_indeg0[i];
	}
	return solution;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	srand(time(0));
	int test_cnt; cin >> test_cnt;
	while (test_cnt--)
	{
		int n; cin >> n;
		vector<int> v(n);
		for (int i = 0; i < n; i++)
			cin >> v[i];
		auto solution = solve(v);
		cout << evaluate(solution, v) << "\n";
		for (int i: solution)
			cout << i << " ";
		cout << "\n";
	}
	return 0;
}