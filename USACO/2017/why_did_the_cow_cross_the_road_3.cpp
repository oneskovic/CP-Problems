#include <algorithm>
#include <iostream>
#include <vector>
#include <set>
using namespace std;

bool is_valid_cell(int row, int col, int n)
{
    return row >= 0 && row < n&& col >= 0 && col < n;
}

vector<int> get_neighbors(int n, int x)
{
    int row = x / n;
    int col = x % n;
    vector<int> drow = { 1,-1,0,0 };
    vector<int> dcol = { 0,0,1,-1 };
    vector<int> neighbors;
    for (int i = 0; i < 4; i++)
    {
        int new_row = row + drow[i];
        int new_col = col + dcol[i];
        if (is_valid_cell(new_row,new_col,n))
            neighbors.push_back(new_row * n + new_col);
    }
    return neighbors;
}

void dfs(int node, const vector<vector<int>>& graph, vector<int>& component, int current_component)
{
    component[node] = current_component;
    for (int neighbor : graph[node])
        if (component[neighbor] == -1)
            dfs(neighbor, graph, component, current_component);    
}

int main()
{
    freopen("countcross.in", "r", stdin);
    freopen("countcross.out", "w", stdout);
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, cow_cnt, road_cnt; cin >> n >> cow_cnt >> road_cnt;
    set<pair<int, int>> removed_edges;
    for (int i = 0; i < road_cnt; i++)
    {
        int r, c, r2, c2;
        cin >> r >> c >> r2 >> c2;
        r--; c--; r2--; c2--;
        int ind1 = r * n + c, ind2 = r2 * n + c2;
        removed_edges.insert({ ind1,ind2 });
        removed_edges.insert({ ind2,ind1 });
    }
    
    vector<vector<int>> graph(n*n, vector<int>());
    for (int i = 0; i < n*n; i++)
    {
        auto neighbors = get_neighbors(n, i);
        for (int neighbor: neighbors)
        {
            if (removed_edges.find({neighbor,i}) == removed_edges.end())
            {
                graph[i].push_back(neighbor);
                graph[neighbor].push_back(i);
            }
        }
    }
    
    vector<int> cows(cow_cnt);
    for (int i = 0; i < cow_cnt; i++)
    {
        int row, col; cin >> row >> col;
        row--; col--;
        cows[i] = row * n + col;
    }
    vector<int> component(n * n, -1);
    int component_cnt = 0;
    for (int i = 0; i < n * n; i++)
        if (component[i] == -1)
            dfs(i, graph, component, component_cnt++);
    
    int sol = 0;
    for (int i = 0; i < cow_cnt; i++)
        for (int j = i+1; j < cow_cnt; j++)
            if (component[cows[i]] != component[cows[j]])
                sol++;
    cout << sol;
    return 0;
}
