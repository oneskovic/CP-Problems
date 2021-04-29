#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main()
{
    freopen("time.in", "r", stdin);
	freopen("time.out", "w", stdout);
    ios::sync_with_stdio(false);
    cin.tie(0);
    int node_cnt, edge_cnt, cost;
    cin>>node_cnt>>edge_cnt>>cost;
    vector<int> node_value(node_cnt);
    for(int i = 0; i < node_cnt; i++)
    {
        cin>>node_value[i];
    }

    vector<vector<int>> neighbors(node_cnt, vector<int>());
    for(int i = 0; i < edge_cnt; i++)
    {
        int a,b;
        cin>>a>>b;
        a--; b--;
        neighbors[b].push_back(a);
    }

    vector<vector<bool>> reachable(node_cnt, vector<bool>(1000, false));
    vector<vector<ll>> dp(node_cnt, vector<ll>(1000));
    reachable[0][0] = 1;
    for(int time = 1; time < 1000; time++)
    {
        for(int node = 0; node < node_cnt; node++)
        {
            bool any_neighbor_reachable = false;
            ll max_over_neighbors = LLONG_MIN;
            for(int neighbor: neighbors[node])
            {
                if(reachable[neighbor][time-1])
                {
                    any_neighbor_reachable = true;
                    max_over_neighbors = max(max_over_neighbors, dp[neighbor][time-1]);
                }
            }
            if(any_neighbor_reachable)
            {
                reachable[node][time] = true;
                dp[node][time] = max_over_neighbors + node_value[node];
            }
        }
    }
    ll solution = 0;
    for(int time = 0; time < 1000; time++)
    {
        solution = max(solution, dp[0][time] - cost*(time*time));
    }
    cout << solution;
    return 0;
}
