#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

vector<int> euler_tour, heights; // The euler tour of the tree, and height of each node
vector<ll> weight_root_node; // Weight of path from root to node i
vector<vector<int>> graph,weights;

class SegmentTree
{
public:
    SegmentTree(const vector<int>& elements);
    // Returns the position of min element
    int min_query(int l, int r);
private:
    vector<int> element_tree, position_tree;
    int element_cnt;
};

void print_vec(const vector<int>& v)
{
    for(auto i : v)
    {
        cout << i << " ";
    }
    cout << "\n";
}

void dfs(int parent, int node, ll current_weight, int current_height)
{
    euler_tour.push_back(node);
    heights.push_back(current_height);
    weight_root_node[node] = current_weight;
    for(int i = 0; i < graph[node].size(); i++)
    {
        int neighbor = graph[node][i];
        if(neighbor != parent)
        {
            dfs(node,neighbor,current_weight + weights[node][i],current_height+1);
            euler_tour.push_back(node);
            heights.push_back(current_height);
        }
    }
    euler_tour.push_back(node);
    heights.push_back(current_height);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n; cin>>n;

    graph = vector<vector<int>>(n+1,vector<int>());
    weights = vector<vector<int>>(n+1,vector<int>());
    for(int i = 0; i < n-1; i++)
    {
        int a,b,weight;
        cin>>a>>b>>weight;
        graph[a].push_back(b);
        graph[b].push_back(a);
        weights[a].push_back(weight);
        weights[b].push_back(weight);
    }

    weight_root_node = vector<ll>(n+1);
    dfs(-1,0,0,0);
    SegmentTree height_tree = SegmentTree(heights);
    vector<int> first_position(n,INT_MAX); // First position of each element in the euler tour
    for(int i = 0; i < euler_tour.size(); i++)
        first_position[euler_tour[i]] = min(first_position[euler_tour[i]],i);

    int query_cnt; cin>>query_cnt;
    for(int q = 0; q < query_cnt; q++)
    {
        int a,b; cin>>a>>b;
        int pos_a = first_position[a], pos_b = first_position[b];

        int lca_position = height_tree.min_query(min(pos_a,pos_b),max(pos_a,pos_b)+1);
        int lca = euler_tour[lca_position];
        ll weight_of_path = weight_root_node[a] + weight_root_node[b] - 2*weight_root_node[lca];
        cout << weight_of_path << "\n";
    }

    return 0;
}

SegmentTree::SegmentTree(const vector<int>& elements)
{
    element_cnt = elements.size();
    element_tree = vector<int>(2*element_cnt);
    position_tree = element_tree;

    copy(elements.begin(),elements.end(),element_tree.begin()+element_cnt);
    iota(position_tree.begin()+element_cnt,position_tree.end(),0);
    for(int i = element_cnt-1; i > 0; i--)
    {
        if(element_tree[2*i] < element_tree[2*i+1])
        {
            element_tree[i] = element_tree[2*i];
            position_tree[i] = position_tree[2*i];
        }
        else
        {
            element_tree[i] = element_tree[2*i+1];
            position_tree[i] = position_tree[2*i+1];
        }
    }
}

int SegmentTree::min_query(int l, int r)
{
    l += element_cnt;
    r += element_cnt;
    int min_el = INT_MAX, min_pos = -1;
    while(l < r)
    {
        if(l%2 == 1)
        {
            if(element_tree[l] <= min_el)
            {
                min_el = element_tree[l];
                min_pos = position_tree[l];
            }
            l++;
        }
        if(r%2== 1)
        {
            r--;
            if(element_tree[r] <= min_el)
            {
                min_el = element_tree[r];
                min_pos = position_tree[r];
            }
        }
        l/=2;
        r/=2;
    }
    return min_pos;
}
