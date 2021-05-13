#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct element
{
    ll dist, utility, delay;
};

bool operator> (const element& lhs, const element& rhs)
{
    return lhs.dist > rhs.dist;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n; cin>>n;
    vector<element> elements(n);
    for(int i = 0; i < n; i++)
    {
        cin>>elements[i].dist;
        cin>>elements[i].utility;
        cin>>elements[i].delay;
    }
    sort(elements.begin(),elements.end(), greater<element>());

    vector<ll> prefix_utility(n);
    map<ll,ll> dist_position;
    prefix_utility[0] = elements[0].utility;
    dist_position[elements[0].dist] = 0;
    ll solution = elements[0].utility;
    for(int i = 1; i < n; i++)
    {
        ll current_dist = elements[i].dist;
        ll delay = elements[i].delay;
        auto ub = dist_position.upper_bound(current_dist + delay);
        ll new_utility = elements[i].utility;
        if(ub != dist_position.end())
        {
            int j = ub->second;
            new_utility = prefix_utility[j] + elements[i].utility;
        }
        prefix_utility[i] = max(prefix_utility[i-1], new_utility);
        solution = max(solution, new_utility);
        dist_position[current_dist] = i;
    }
    cout << solution << "\n";
    return 0;
}
