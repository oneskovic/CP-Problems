#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;
#define INF 5e5

int update_dist(int node, vector<vector<int>>& tree, vector<int>& dist_to_black, int max_dist = INF, int current_dist = 0, int parent = -1)
{
	if (current_dist > max_dist)
		return INF;
	
	if (dist_to_black[node] <= current_dist)
		return dist_to_black[node];
	dist_to_black[node] = current_dist;
	
	int min_dist_to_other_black = INF;
	for (int neighbor: tree[node])
	{
		if (neighbor != parent)
		{
			int d = update_dist(neighbor, tree, dist_to_black, max_dist, current_dist + 1, node);
			min_dist_to_other_black = min(d+1, min_dist_to_other_black);
		}
	}
	return min_dist_to_other_black;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int test_cnt; cin >> test_cnt;
	while (test_cnt--)
	{
		int n, root; cin >> n >> root;
		root--;
		vector<int> operations(n);
		for (int i = 0; i < n-1; i++)	
			cin >> operations[i], operations[i]--;
		
		vector<vector<int>> tree(n, vector<int>());
		for (int i = 0; i < n-1; i++)
		{
			int u, v; cin >> u >> v;
			u--; v--;
			tree[u].push_back(v);
			tree[v].push_back(u);
		}
		vector<int> dist_to_black(n, INF);
		update_dist(root, tree, dist_to_black);
		int min_dist = update_dist(operations[0], tree, dist_to_black);
		cout << min_dist << " ";
		for (int i = 1; i < n-1; i++)
		{
			min_dist = min(update_dist(operations[i], tree, dist_to_black, min_dist), min_dist);
			cout << min_dist << " ";
		}
		cout << endl;
	}


	return 0;
}