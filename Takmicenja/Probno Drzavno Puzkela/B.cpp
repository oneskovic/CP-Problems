#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <numeric>
#include <queue>
using namespace std;
typedef long long ll;

class DSU
{
public:
    DSU(int max_element);
    void join_sets(int element1, int element2);
    int find_set(int element);
    vector<int> representative;
private:
    vector<int> set_size;
};


pair<vector<int>,vector<int>> topological_sort(const vector<vector<int>>& graph, vector<int>& indegree, const vector<int>& renamed_coins, vector<int>& vertices)
{
    int n = graph.size();
    vector<int> node_order;
    map<int,int> cnt_nodes_assigned_index;
    map<int,int> node_index;

    queue<int> indegree_zero;
    for(int i: vertices)
    {
        if(indegree[i] == 0 && renamed_coins[i] == i)
        {
            indegree_zero.push(i);
            node_index[i] = 0;
            cnt_nodes_assigned_index[0]++;
        }
    }
    while(!indegree_zero.empty())
    {
        bool index_known = indegree_zero.size() == 1 ? 1 : 0; 
        int current_node = indegree_zero.front();

        for(int neighbor: graph[current_node])
        {
            indegree[neighbor]--;
            if(indegree[neighbor] == 0 && renamed_coins[neighbor] == neighbor)
            {
                indegree_zero.push(neighbor);
                node_index[neighbor] = node_index[current_node] + 1;
                cnt_nodes_assigned_index[node_index[neighbor]]++;
            }
        }
        node_order.push_back(indegree_zero.front());
        indegree_zero.pop();
    }
    vector<int> index_given; index_given.reserve(node_order.size());
    for(int i: node_order)
    {
        int index = node_index[i];
        if (cnt_nodes_assigned_index[index] > 1)
            index_given.push_back(-1);
        else
            index_given.push_back(index);
    }
    return {node_order, index_given};
}

void dfs(int node, const vector<vector<int>>& graph, DSU& components_dsu, int current_component)
{  
    components_dsu.join_sets(current_component, node);
    for(int neighbor: graph[node])
    {
        components_dsu.join_sets(current_component, neighbor);
        dfs(neighbor, graph, components_dsu, current_component);
    }
}

vector<vector<int>> get_components(const vector<vector<int>>& graph, vector<int>& renamed_coins)
{
    int n = graph.size();
    DSU component_dsu(n);
    for (int i = 0; i < n; i++)
    {
        if(component_dsu.find_set(i) == i && renamed_coins[i] == i)
        {
            dfs(i,graph,component_dsu,i);
        }
    }
    vector<vector<int>> components(n,vector<int>());
    for (int i = 0; i < n; i++)
    {
        if(renamed_coins[i] != i)
            continue;
        components[component_dsu.representative[i]].push_back(i);
    }
    vector<vector<int>> nonempty_components; nonempty_components.reserve(components.size());
    for(int i = 0; i < n; i++)
    {
        if(!components[i].empty())
            nonempty_components.push_back(components[i]);
    }
    
    return nonempty_components;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int cnt_types, cnt_coins, cnt_comps; 
    cin >> cnt_types>>cnt_coins>>cnt_comps;

    vector<vector<int>> graph(cnt_coins, vector<int>());
    vector<pair<int,int>> edges; edges.reserve(cnt_comps);
    DSU dsu = DSU(cnt_coins);
    for (int i = 0; i < cnt_comps; i++)
    {
        string s; cin>>s;
        int op_pos = -1;
        for (int j = 0; j < s.size(); j++)
        {
            if(s[j] == '<' || s[j] == '>' || s[j] == '=')
            {
                op_pos = j;
                break;
            }
        }
        string l = string(s.begin(),s.begin()+op_pos);
        string r = string(s.begin()+op_pos+1, s.end());
        int a = stoi(l);
        int b = stoi(r);
        a--; b--;
        if (s[op_pos] == '<')
        {
            edges.push_back({a,b});
        }
        else if(s[op_pos] == '>')
        {
            edges.push_back({b,a});
        }
        else
        {
            dsu.join_sets(a,b);
        }
    }
    
    vector<int> renamed_coins = dsu.representative;
    vector<vector<int>> coins_renamed_as_coin(cnt_coins,vector<int>());
    for (int i = 0; i < cnt_coins; i++)
        coins_renamed_as_coin[renamed_coins[i]].push_back(i);

    vector<pair<int,int>> renamed_edges; renamed_edges.reserve(edges.size());
    for(auto edge: edges)
    {
        int a = renamed_coins[edge.first];
        int b = renamed_coins[edge.second];
        renamed_edges.push_back({a,b});
    }
    sort(renamed_edges.begin(),renamed_edges.end());
    renamed_edges.erase(unique(renamed_edges.begin(),renamed_edges.end()),renamed_edges.end());

    vector<int> in_degree(cnt_coins);
    for(auto edge: renamed_edges)
    {
        int a = edge.first;
        int b = edge.second;
        graph[a].push_back(b);
        in_degree[b]++;
    }

    auto components = get_components(graph, renamed_coins);
    vector<int> solution(cnt_coins, -1);
    for(auto& component: components)
    {
        auto sorted = topological_sort(graph,in_degree,renamed_coins, component);
        auto& coin_order = sorted.first;
        auto& coin_index = sorted.second; 
        if(coin_index.back() == cnt_types-1)
        {
            for(int i = 0; i < coin_order.size(); i++)
            {
                int node = coin_order[i];
                solution[node] = coin_index[i];
            }
        }
    }
    
    for (int i = 0; i < cnt_coins; i++)
    {
        if(renamed_coins[i] != i)
            continue;
        int coin_pos = solution[i];
        for(int c: coins_renamed_as_coin[i])
            solution[c] = coin_pos;
    }
    for(int i = 0; i < cnt_coins; i++)
    {
        if(solution[i] == -1)
            cout << "?\n";
        else
            cout << "K" << solution[i]+1 << "\n";

    }
        
    return 0;
}

int DSU::find_set(int element)
{
    if(representative[element] == element)
        return element;
    representative[element] = find_set(representative[element]);
    return representative[element];
}

void DSU::join_sets(int element1, int element2)
{
    int a = find_set(element1);
    int b = find_set(element2);
    if (a != b) {
        if (set_size[a] < set_size[b])
            swap(a, b);
        representative[b] = a;
        set_size[a] += set_size[b];
    }
}

DSU::DSU(int max_element)
{
    representative = vector<int>(max_element);
    iota(representative.begin(),representative.end(),0);
    set_size = vector<int>(max_element,1);
}