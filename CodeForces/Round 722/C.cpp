#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void topological_sort(int parent, int node, vector<int>& result, vector<vector<int>>& children, const vector<vector<int>>& graph)
{
    for(int neighbor: graph[node])
    {
        if(neighbor != parent)
        {
            children[node].push_back(neighbor);
            topological_sort(node,neighbor,result,children,graph);
        }
    }
    result.push_back(node);
}
void print_vec(vector<vector<ll>> v)
{
    for(auto row: v)
    {
        for(auto col: row)
        {
            cout << col << " ";
        }
        cout << "\n";
    }
    cout<<"\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int test_cnt; cin>>test_cnt;
    while(test_cnt--)
    {
        int n; cin>>n;
        vector<vector<int>> graph(n,vector<int>());
        vector<vector<ll>> low_high_values(n,vector<ll>(2));
        vector<int> degree(n);

        for(int i = 0; i < n; i++)
            cin>>low_high_values[i][0] >> low_high_values[i][1];
        for(int i = 0; i < n-1; i++)
        {
            int a,b; cin>>a>>b;
            a--; b--;
            graph[a].push_back(b);
            graph[b].push_back(a);
        }

        vector<int> node_order;
        vector<vector<int>> children (n,vector<int>());
        vector<vector<ll>> dp(n,vector<ll>(2));
        topological_sort(-1,0,node_order,children,graph);

        for(int node: node_order)
        {
            if(children[node].empty())
            {
                dp[node][0] = 0;
                dp[node][1] = 0;
            }
            else
            {
                for(int child: children[node])
                {
                    ll node_l = low_high_values[node][0],
                    node_h = low_high_values[node][1],
                    child_l = low_high_values[child][0],
                    child_h = low_high_values[child][1];

                    dp[node][0] += max(dp[child][0] + abs(node_l - child_l),dp[child][1] + abs(node_l - child_h));

                    dp[node][1] += max(dp[child][0] + abs(node_h - child_l),dp[child][1] + abs(node_h - child_h));
                }
            }
        }
        cout << max(dp[0][0],dp[0][1]) << "\n";
    }
    return 0;
}
