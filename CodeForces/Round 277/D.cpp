#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#define ll long long
const ll mod = 1000000007;

// Gadan kod :P
ll count_dfs(int parent, int current_node, const vector<vector<int>>& adj, const vector<int>& value, const int max_value, const int max_difference, const int start_node)
{
	ll valid_sets = 1;
	for (int neighbor: adj[current_node])
	{
		int current_difference = max_value - value[neighbor];
		if (neighbor != parent && 
			(value[neighbor] < max_value || (value[neighbor] == max_value && neighbor < start_node))&&
			current_difference <= max_difference)
		{
			
			valid_sets *= (count_dfs(current_node, neighbor, adj, value, max_value, max_difference, start_node)+1);
			valid_sets %= mod;
		}
	}
	return valid_sets % mod;
}

ll count_valid_sets(const vector<vector<int>>& adjacent, const vector<int>& value, const int max_difference)
{
	ll total_valid_sets = 0;
	for (size_t i = 1; i < adjacent.size(); i++)
	{
		total_valid_sets += count_dfs(-1, i, adjacent, value, value[i], max_difference, i);
		total_valid_sets %= mod;
	}
	return total_valid_sets % mod;
}

int main()
{
	ios::sync_with_stdio(false);
	int max_difference, number_of_nodes; cin >> max_difference >> number_of_nodes;
	vector<int> value(number_of_nodes+1);
	for (size_t i = 1; i <= number_of_nodes; i++)
		cin >> value[i];
	
	vector<vector<int>> adjacent(number_of_nodes+1);
	for (size_t i = 0; i <= number_of_nodes; i++)
		adjacent[i] = vector<int>();
	
	for (size_t i = 0; i < number_of_nodes-1; i++)
	{
		int node1, node2; cin >> node1 >> node2;
		adjacent[node1].push_back(node2);
		adjacent[node2].push_back(node1);
	}
	cout << count_valid_sets(adjacent, value, max_difference);
	return 0;
}