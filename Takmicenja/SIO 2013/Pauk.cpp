#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
#define ll long long
const ll mod = 1e9 + 7;


ll count_combinations(const vector<int>& elements, int choice_count)
{
	vector<vector<ll>> dp(choice_count + 1, vector<ll>(elements.size()));

	ll sum = 0;
	for (int i = elements.size() - 1; i >= 0; i--)
	{
		sum += elements[i];
		dp[1][i] = sum;
	}

	for (size_t remaining = 2; remaining <= choice_count; remaining++)
	{
		for (int position = elements.size() - 2; position >= 0; position--)
		{
			dp[remaining][position] = elements[position] * dp[remaining - 1][position + 1] + dp[remaining][position + 1];
			dp[remaining][position] %= mod;
		}
	}
	return dp[choice_count][0]%mod;
}

ll solution = 0;
int k;
void dfs(int parent, int current_node, int depth, const vector<vector<int>>& adj, vector<vector<int>>& dp)
{
	dp[current_node][0] = 1;
	for (int neighbor: adj[current_node])
	{
		if (neighbor != parent)
		{
			dfs(current_node, neighbor, depth + 1, adj, dp);
			for (size_t i = 0; i < dp[neighbor].size() - 1; i++)
			{
				int path_length = i + 1;
				dp[current_node][path_length] += dp[neighbor][i];
			}
		}
	}
	for (size_t path_length = 1; path_length <= dp[1].size(); path_length++)
	{
		vector<int> neighbor_paths;
		if (depth >= path_length)
			neighbor_paths.push_back(1);
		
		for (int neighbor : adj[current_node])
			if (neighbor != parent && dp[neighbor][path_length - 1] > 0)
				neighbor_paths.push_back(dp[neighbor][path_length - 1]);
				
		if (neighbor_paths.size() >= 3 && neighbor_paths.size()*path_length >= k-1)
		{
			int choice_count = (k - 1) / path_length;
			solution += count_combinations(neighbor_paths,choice_count);
			solution %= mod;
		}
	}
	
}

int main()
{
	int node_count; 
	cin >> node_count >> k;
	vector<vector<int>> adjacent(node_count+1,vector<int>());
	vector<vector<int>> dp(node_count+1, vector<int>((k - 1)/3 + 1));
	for (size_t i = 0; i < node_count-1; i++)
	{
		int a, b;
		cin >> a >> b;
		adjacent[a].push_back(b);
		adjacent[b].push_back(a);
	}
	dfs(-1, 1, 0, adjacent, dp);
	cout << solution%mod <<"\n";
	return 0;
}