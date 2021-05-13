#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

stack<int> current_path, longest_path;
int max_dist = -1;
void furthest_node(int node, int parent, int current_dist, const vector<vector<int>>& tree)
{
    if(current_dist > max_dist)
    {
        longest_path = current_path;
        max_dist = current_dist;
    }
    for(int child: tree[node])
    {
        if(child != parent)
        {
            current_path.push(child);
            furthest_node(child, node, current_dist+1, tree);
            current_path.pop();
        }
    }
}

vector<int> disconnected_nodes;
set<pair<int,int>> disconnections;
void disconnect_recursive(int node, int parent, const vector<vector<int>>& tree)
{
    disconnected_nodes.push_back(node);
    disconnections.insert({min(parent,node),max(parent,node)});
    for(int child: tree[node])
    {
        if(child != parent)
        {
            disconnect_recursive(child, node, tree);
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int test_cnt; cin>>test_cnt;
    while(test_cnt--)
    {
        longest_path = stack<int>();
        current_path = stack<int>();
        max_dist = -1;
        disconnected_nodes = vector<int>();
        disconnections = set<pair<int,int>>();

        int n; cin>>n;
        vector<vector<int>> tree(n+1,vector<int>());
        for(int i = 0 ; i < n-1; i++)
        {
            int a, b; cin>>a>>b;
            tree[a].push_back(b);
            tree[b].push_back(a);
        }

        current_path.push(1);
        furthest_node(1,-1,0,tree);
        int n1 = longest_path.top();

        longest_path = stack<int>();
        current_path = stack<int>();
        max_dist = -1;

        current_path.push(n1);
        furthest_node(n1,-1,0,tree);
        int n2 = longest_path.top();
        longest_path.pop();
        int prev_node = n2;
        while(!longest_path.empty())
        {
            int current_node = longest_path.top();
            longest_path.pop();
            int next_node = -1;
            if(!longest_path.empty())
                next_node = longest_path.top();
            for(int child: tree[current_node])
            {
                if(child != prev_node && child != next_node)
                {
                    disconnect_recursive(child,current_node,tree);
                }
            }
            prev_node = current_node;
        }

        prev_node = n2;
        set<pair<int,int>> connections;
        for(int node: disconnected_nodes)
        {
            auto edge = pair<int,int>(min(node,prev_node), max(node,prev_node));
            connections.insert(edge);
            prev_node = node;
        }
        vector<pair<int,int>> to_delete;
        for(auto e: connections)
        {
            if(disconnections.find(e) != disconnections.end())
            {
                to_delete.push_back(e);
                disconnections.erase(e);
            }
        }
        for(auto e: to_delete)
            connections.erase(e);

        vector<pair<int,int>> connections_vec(connections.begin(),connections.end());
        vector<pair<int,int>> disconnections_vec(disconnections.begin(), disconnections.end());
        cout << connections.size() << "\n";
        for(int i = 0; i < connections_vec.size(); i++)
        {
            cout << disconnections_vec[i].first << " " << disconnections_vec[i].second << " " << connections_vec[i].first << " " << connections_vec[i].second << "\n";
        }
    }
    return 0;
}
