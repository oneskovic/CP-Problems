#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>
#include <string>
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
        if (is_valid_cell(new_row, new_col, n))
            neighbors.push_back(new_row * n + new_col);
    }
    return neighbors;
}

int dfs(int node, const vector<vector<int>>& graph,const vector<bool>& is_filled, vector<int>& component, int current_component)
{
    component[node] = current_component;
    int area = 1;
    for (int neighbor : graph[node]) {
        if (component[neighbor] == -1 && is_filled[neighbor]) {
            area += dfs(neighbor, graph, is_filled, component, current_component);
        }
    }
    return area;
}

int get_node_perimeter(int node, const vector<vector<int>>& graph, vector<int>& component, int n)
{
    auto neighbors = get_neighbors(n, node);
    int perimeter = 0;
    for (int neighbor : neighbors)
        if (component[neighbor] != component[node])
            perimeter++;

    return perimeter;
}

int main()
{
    freopen("perimeter.in", "r", stdin);
    freopen("perimeter.out", "w", stdout);
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n; cin >> n;
    vector<bool> is_filled((n+2) * (n+2));
    for (int i = 1; i < n+1; i++)
    {
        string s; cin >> s;
        for (int j = 1; j < n+1; j++) {
            if (s[j-1] == '#') {
                int ind = i * (n+2) + j;
                is_filled[ind] = 1;
            }
        }
    }
    n += 2;
    vector<vector<int>> graph(n * n, vector<int>());
    for (int i = 0; i < n * n; i++)
    {
        auto neighbors = get_neighbors(n, i);
        for (int neighbor : neighbors)
        {
            graph[i].push_back(neighbor);
        }
    }

    vector<int> component_area;
    int component_cnt = 0;
    vector<int> component(n*n,-1);
    for (int i = 0; i < n*n; i++)
    {
        if (component[i] == -1 && is_filled[i])
        {
            int area = dfs(i, graph, is_filled, component, component_cnt++);
            component_area.push_back(area);
        }
    }
    vector<int> component_perimeter(component_cnt);
    for (int i = 0; i < n*n; i++)
        if (is_filled[i])
            component_perimeter[component[i]]+= get_node_perimeter(i, graph, component, n);
        
    vector<int> components_sorted(component_cnt);
    iota(components_sorted.begin(), components_sorted.end(), 0);
    sort(components_sorted.begin(), components_sorted.end(),
        [component_area, component_perimeter](int lhs, int rhs) {
            pair<int, int> comp1 = { component_area[lhs],component_perimeter[lhs] };
            pair<int, int> comp2 = { component_area[rhs],component_perimeter[rhs] };
            return comp1 > comp2;
        });
    int sol_comp = components_sorted[0];
    cout << component_area[sol_comp] << " " << component_perimeter[sol_comp] << "\n";

    return 0;
}
