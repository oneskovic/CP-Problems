#include <algorithm>
#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <queue>
using namespace std;
typedef long long ll;

void dfs(int node, int parent, vector<int>& parents, const vector<vector<int>>& adj)
{
    parents[node] = parent + 1;
    for (int neighbor: adj[node])
    {
        if (neighbor != parent)
        {
            dfs(neighbor, node, parents, adj);
        }
    }
}

vector<int> generate_tree(int n)
{
    vector<int> prufer_seq(n - 2);
    for (int i = 0; i < n - 2; i++)
    {
        prufer_seq[i] = rand() % n + 1;
    }

    vector<int> degree(n + 1);
    vector<vector<int>> adj = vector<vector<int>>(n + 1, vector<int>());
    for (int i = 1; i <= n; i++)
        degree[i] = 1;
    for (int i : prufer_seq)
        degree[i]++;
    for (int i : prufer_seq)
    {
        for (int j = 1; j <= n; j++)
        {
            if (degree[j] == 1)
            {
                adj[i-1].push_back(j-1);
                adj[j-1].push_back(i-1);
                degree[i]--;
                degree[j]--;
                break;
            }
        }
    }
    int u = 0, v = 0;
    for (int i = 1; i <= n; i++)
    {
        if (degree[i] == 1)
        {
            if (u == 0)
                u = i;
            else
            {
                v = i;
                break;
            }
        }
    }
    adj[u-1].push_back(v-1);
    adj[v-1].push_back(u-1);

    /*for (int i = 0; i < adj.size(); i++)
    {
        for (auto x: adj[i])
        {
            cout << i << " " << x << "\n";
        }
    }*/

    vector<int> dag(adj.size());
    dfs(0, -1, dag, adj);
    return dag;
}

ll bruteforce(int n, int m, vector<int> tree, vector<ll> input_times, vector<ll> input_nodes)
{
    vector<int> cards_at_node(tree.size());
    vector<pair<ll, ll>> time_card(tree.size());
    for (int i = 0; i < input_times.size(); i++)
    {
        time_card[i] = { input_times[i], input_nodes[i]-- };
    }
    sort(time_card.begin(), time_card.end());

    int card_index = 0;
    ll solution = 0;
    for (int t = 0; t <= time_card.back().first; t++)
    {
        for (int node = 0; node < tree.size(); node++)
        {
            int parent = tree[node];
            if (cards_at_node[parent] == 1)
            {
                cards_at_node[parent] = 0;
                solution += 2;
            }
            else
                cards_at_node[parent] = 1;
            
            cards_at_node[node] = 0;
        }
        while (time_card[card_index].first == t)
        {
            cards_at_node[time_card[card_index].second]++;
            int prev_cnt = cards_at_node[time_card[card_index].second];
            cards_at_node[time_card[card_index].second] %= 2;
            solution += prev_cnt - cards_at_node[time_card[card_index].second];
        }
    }
    return solution;
}

vector<int> topsort(const vector<vector<int>>& dag, const vector<int>& parent)
{
    vector<int> degree(dag.size());
    queue<int> deg_zero_nodes;
    for (int i = 0; i < dag.size(); i++)
    {
        if (dag[i].size() == 0)
            deg_zero_nodes.push(i);
        degree[i] = dag[i].size();
    }

    vector<int> solution; solution.reserve(dag.size());
    while (!deg_zero_nodes.empty())
    {
        int node = deg_zero_nodes.front();
        deg_zero_nodes.pop();
        solution.push_back(node);
        if (parent[node] != -1)
        {
            degree[parent[node]]--;
            if (degree[parent[node]] == 0)
                deg_zero_nodes.push(parent[node]);
        }
    }
    return solution;
}

ll merge_sets(set<ll>& larger_set, ll larger_set_delta, const set<ll>& smaller_set, ll smaller_set_delta)
{
    ll erased_cnt = 0;
    for (ll x : smaller_set)
    {
        ll real_time = x + smaller_set_delta;
        ll time_in_larger_set = real_time - larger_set_delta;
        if (larger_set.find(time_in_larger_set) != larger_set.end())
        {
            larger_set.erase(time_in_larger_set);
            erased_cnt += 2;
        }
        else
        {
            larger_set.insert(time_in_larger_set);
        }
    }
    return erased_cnt;
}


ll neskovic(int n, int m, vector<int> tree, vector<ll> input_times, vector<ll> input_nodes)
{
    vector<vector<int>> dag(n, vector<int>());
    vector<int> parent(n, -1);
    for (int i = 0; i < n - 1; i++)
    {
        tree[i]--;
        dag[tree[i]].push_back(i + 1);
        parent[i + 1] = tree[i];
    }

    vector<set<ll>*> times_in_node(n);
    for (int i = 0; i < n; i++)
    {
        times_in_node[i] = new set<ll>();
    }
    vector<ll> time_offsets(n, 0);


    ll solution = 0;
    for (int i = 0; i < m; i++)
    {
        ll time = input_times[i]; int node = input_nodes[i];
        node--;
        if (times_in_node[node]->find(time) != times_in_node[node]->end())
        {
            solution += 2;
            times_in_node[node]->erase(time);
        }
        else
            times_in_node[node]->insert(time);
    }

    auto sorted_nodes = topsort(dag, parent);
    for (int node : sorted_nodes)
    {
        set<ll>* merged_children_set = new set<ll>();
        ll merged_children_offset = 0;

        for (int child : dag[node])
        {
            if (times_in_node[child]->size() > merged_children_set->size())
            {
                solution += merge_sets(*times_in_node[child], time_offsets[child], *merged_children_set, merged_children_offset);
                merged_children_set = times_in_node[child];
                merged_children_offset = time_offsets[child];
            }
            else
            {
                solution += merge_sets(*merged_children_set, merged_children_offset, *times_in_node[child], time_offsets[child]);
            }
        }

        if (times_in_node[node]->size() > merged_children_set->size())
        {
            solution += merge_sets(*times_in_node[node], time_offsets[node], *merged_children_set, merged_children_offset + 1);
        }
        else
        {
            solution += merge_sets(*merged_children_set, merged_children_offset, *times_in_node[node], time_offsets[node] - 1);
            times_in_node[node] = merged_children_set;
            time_offsets[node] = merged_children_offset + 1;
        }
    }
    return solution;
}

struct card
{
    int time;
    int node;
};


ll sek(int n, int m, vector<int> input_ancestor, vector<ll> input_times, vector<ll> input_nodes)
{
    vector<int> depth(n);
    vector<vector<int>> children(n);
    for (int node = 1; node < n; node++)
    {
        int ancestor = input_ancestor[node-1]; ancestor--;
        children[ancestor].push_back(node);
    }
    queue<int> queue; queue.push(0);
    while (!queue.empty())
    {
        int node = queue.front(); queue.pop();
        for (int child : children[node])
        {
            queue.push(child);
            depth[child] = depth[node] + 1;
        }
    }

    vector<card> cards(m);
    for (int i = 0; i < m; i++)
    {
        int t = input_times[i], v = input_nodes[i];
        cards[i].time = t;
        cards[i].node = v - 1;
    }
    sort(cards.begin(), cards.end(), [](card a, card b) { return a.time < b.time; });
    vector<vector<int>> card_snapshots;
    int snapshot = 0;
    card_snapshots.push_back(vector<int>());
    card_snapshots[0].push_back(cards[0].node);
    int throwaway_cnt = 0;
    map<int, int> card_depth;
    for (int i = 1; i < m; i++)
    {
        card_depth[depth[node] + cards[i].time]++;
        if (card_depth[depth[node] + snapshot] % 2 == 0) throwaway_cnt += 2;
    }

    
    for (int snapshot = 0; snapshot < card_snapshots.size(); snapshot++)
    {
        for (int node : card_snapshots[snapshot])
        {
            card_depth[depth[node] + cards[]++;
            if (card_depth[depth[node] + snapshot] % 2 == 0) throwaway_cnt += 2;
        }
    }

    return throwaway_cnt;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    srand(69);

    int test_cnt; cin >> test_cnt;
    while (test_cnt--)
    {
        int n = rand() % 100 + 1, m = rand()%100 + 1;
        auto tree = generate_tree(max(2,n));
        tree.erase(tree.begin());
        vector<ll> nodes(m);
        vector<ll> times(m);
        for (int i = 0; i < m; i++)
        {
            nodes[i] = rand() % n + 1;
            times[i] = rand() % 100;
        }
        ll sol1 = neskovic(n, m, tree, times, nodes);
        ll sol2 = sek(n, m, tree, times, nodes);
        ll sol3 = bruteforce(n, m, tree, times, nodes);
        if (sol1 != sol2)
        {
            cout << "wa\n";
        }
        else
            cout << "ok\n";
    }

    return 0;
}
