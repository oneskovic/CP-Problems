#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <numeric>
using namespace std;
typedef long long ll;

const ll INF = INT_MAX;
int bfs(int s, int t, vector<int>& parent, const vector<vector<int>>& adj, const vector<vector<ll>>& capacity) {
    fill(parent.begin(), parent.end(), -1);
    parent[s] = -2;
    queue<pair<int, int>> q;
    q.push({ s, INF });

    while (!q.empty()) {
        ll cur = q.front().first;
        ll flow = q.front().second;
        q.pop();

        for (int next : adj[cur]) {
            if (parent[next] == -1 && capacity[cur][next]) {
                parent[next] = cur;
                ll new_flow = min(flow, capacity[cur][next]);
                if (next == t)
                    return new_flow;
                q.push({ next, new_flow });
            }
        }
    }

    return 0;
}

ll maxflow(int n, vector<vector<ll>>& capacity, vector<vector<int>> adj, int s, int t) {
    ll flow = 0;
    vector<int> parent(n);
    ll new_flow;

    while (new_flow = bfs(s, t, parent, adj, capacity)) {
        flow += new_flow;
        int cur = t;
        while (cur != s) {
            int prev = parent[cur];
            capacity[prev][cur] -= new_flow;
            capacity[cur][prev] += new_flow;
            cur = prev;
        }
    }

    return flow;
}

pair<vector<vector<int>>, vector<vector<ll>>> initialize_graph(const vector<ll>& sources, const vector<ll>& needs)
{
    int src = 0;
    int SO = 1, SA = 2, SB = 3, SAB = 4;
    int NO = 5, NA = 6, NB = 7, NAB = 8;
    int dest = 9;
    vector<vector<int>> adj(10, vector<int>());
    vector<vector<ll>> cap(10, vector<ll>(10, 0));
    adj[src] = { SO,SA,SB,SAB };
    for (int i = 0; i < 4; i++)
        cap[src][adj[src][i]] = sources[i];


    adj[SO] = { NO,NA,NB,NAB };
    for (int n : adj[SO])
        cap[SO][n] = INF;


    adj[SA] = { NA,NAB };
    for (int n : adj[SA])
        cap[SA][n] = INF;


    adj[SB] = { NB, NAB };
    for (int n : adj[SB])
        cap[SB][n] = INF;


    adj[SAB] = { NAB };
    for (int n : adj[SAB])
        cap[SAB][n] = INF;


    adj[NO] = { dest };
    cap[NO][dest] = needs[0];

    adj[NA] = { dest };
    cap[NA][dest] = needs[1];

    adj[NB] = { dest };
    cap[NB][dest] = needs[2];

    adj[NAB] = { dest };
    cap[NAB][dest] = needs[3];

    return { adj, cap };
}

vector<vector<pair<ll, int>>> parse_flows(const vector<vector<ll>>& cap, const vector<vector<int>>& adj)
{
    int src = 0;
    int SO = 1, SA = 2, SB = 3, SAB = 4;
    int NO = 5, NA = 6, NB = 7, NAB = 8;
    int dest = 9;
    vector<vector<pair<ll, int>>> sol(4,vector<pair<ll,int>>());
    vector<int> sources = { 1,2,3,4 };
    vector<int> map_dests(10);
    map_dests[NO] = 0;
    map_dests[NA] = 1;
    map_dests[NB] = 2;
    map_dests[NAB] = 3;

    for (int src_node: sources)
    {
        for (int dest_node: adj[src_node])
        {
            ll assigned_flow = INF - cap[src_node][dest_node];
            sol[map_dests[dest_node]].push_back({ assigned_flow, src_node - 1 });
        }
    }
    return sol;
}

void assign_patient(int patient_group, ll patient_need, vector<vector<pair<ll, int>>>& available_resources)
{
    auto available_groups_for_patient = available_resources[patient_group];
    vector<ll> taken_ammounts = { 0,0,0,0 };
    while (patient_need > 0)
    {
        ll to_take = min(patient_need, available_resources[patient_group][0].first);
        patient_need -= to_take;
        taken_ammounts[available_resources[patient_group][0].second] = to_take;
        available_resources[patient_group][0].first -= to_take;
        if (available_resources[patient_group][0].first == 0)
        {
            available_resources[patient_group].erase(available_resources[patient_group].begin());
        }
    }
    for (ll i: taken_ammounts)
    {
        cout << i << " ";
    }
    cout << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int patient_cnt; cin >> patient_cnt;
    vector<ll> sources(4);
    for (int i = 0; i < 4; i++)
        cin >> sources[i];
    vector<ll> needs(4);
    vector<pair<int, ll>> patient_needs(patient_cnt);
    for (int i = 0; i < patient_cnt; i++)
    {
        string group; cin >> group;
        int int_group = 0;
        ll amount; cin >> amount;
        if (group == "O")
        {
            needs[0] += amount;
            int_group = 0;
        }
        else if (group == "A")
        {
            needs[1] += amount;
            int_group = 1;
        }
        else if (group == "B")
        {
            needs[2] += amount;
            int_group = 2;
        }
        else
        {
            needs[3] += amount;
            int_group = 3;
        }
        patient_needs[i] = {int_group, amount};
    }

    auto g = initialize_graph(sources, needs);
    int src = 0, dest = 9;

    ll flow = maxflow(10, g.second, g.first, src, dest);
    ll sum_needs = accumulate(needs.begin(), needs.end(), (ll)0);
    if (flow == sum_needs)
    {
        cout << "moguce\n";
        auto parsed = parse_flows(g.second, g.first);
        for (auto patient: patient_needs)
        {
            assign_patient(patient.first, patient.second, parsed);
        }
    }
    else
    {
        cout << "nemoguce\n";
    }
    return 0;
}