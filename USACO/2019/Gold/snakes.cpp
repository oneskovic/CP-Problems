#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

class TwoSmallest
{
public:
    TwoSmallest();
    void update(ll new_val, int val_index);
    ll first_smallest, second_smallest;
    int first_smallest_index, second_smallest_index;
};
TwoSmallest::TwoSmallest()
{
    first_smallest = LLONG_MAX;
    second_smallest = LLONG_MAX;
    first_smallest_index = -1;
    second_smallest_index = -1;
}
void TwoSmallest::update(ll new_val, int val_index)
{
    if(new_val <= first_smallest)
    {
        second_smallest = first_smallest;
        second_smallest_index = first_smallest_index;

        first_smallest = new_val;
        first_smallest_index = val_index;
    }
    else if(new_val <= second_smallest)
    {
        second_smallest = new_val;
        second_smallest_index = val_index;
    }
}

void print_vec(vector<TwoSmallest> v)
{
    for(TwoSmallest e: v)
    {
        cout << "(" << e.first_smallest << "," << e.first_smallest_index << "),(" << e.second_smallest << "," << e.second_smallest_index << ")\n";
    }
}

void print_vec(vector<vector<ll>> v)
{
    for(auto row: v)
    {
        for(auto e: row)
        {
            if(e == LLONG_MAX)
                cout << "x ";
            else
                cout << e << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}

int main()
{
    freopen("snakes.in", "r", stdin);
	freopen("snakes.out", "w", stdout);
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n,k ; cin>>n >> k;
    vector<int> elements(n);
    for(int i = 0; i < n; i++)
        cin>>elements[i];
    auto net_sizes = elements;
    sort(net_sizes.begin(),net_sizes.end());
    net_sizes.erase(unique(net_sizes.begin(),net_sizes.end()),net_sizes.end());
    vector<int> position_in_sorted(1e6+1);
    for(int i = 0; i < net_sizes.size(); i++)
        position_in_sorted[net_sizes[i]] = i;

    vector<vector<ll>> dp(net_sizes.size(),vector<ll>(k+1, LLONG_MAX));
    vector<TwoSmallest> dp_min(k+1,TwoSmallest());
    for(int index = position_in_sorted[elements[0]]; index < dp.size(); index++)
    {
        dp[index][0] = net_sizes[index] - elements[0];
        dp_min[0].update(dp[index][0], index);
    }
    //print_vec(dp_min);
    //print_vec(dp);
    for(int position = 1; position < n; position++)
    {
        auto prev_dp = dp;
        auto prev_dp_min = dp_min;
        dp = vector<vector<ll>>(dp.size(),vector<ll>(k+1, LLONG_MAX));
        dp_min = vector<TwoSmallest>(k+1, TwoSmallest());

        for(int net_size_index = position_in_sorted[elements[position]]; net_size_index < dp.size(); net_size_index++)
        {
            ll wasted_space = net_sizes[net_size_index] - elements[position];
            dp[net_size_index][0] = prev_dp[net_size_index][0];
            if(dp[net_size_index][0] < LLONG_MAX - wasted_space)
            {
                dp[net_size_index][0] += wasted_space;
            }

            dp_min[0].update(dp[net_size_index][0], net_size_index);
            for(int delta = 1; delta <= k; delta++)
            {
                if(prev_dp_min[delta-1].first_smallest_index == net_size_index)
                {
                    dp[net_size_index][delta] = prev_dp_min[delta-1].second_smallest;
                }
                else
                {
                    dp[net_size_index][delta] = prev_dp_min[delta-1].first_smallest;
                }
                dp[net_size_index][delta] = min(dp[net_size_index][delta], prev_dp[net_size_index][delta]);
                if(dp[net_size_index][delta] < LLONG_MAX - wasted_space)
                {
                    dp[net_size_index][delta] += wasted_space;
                }
                dp_min[delta].update(dp[net_size_index][delta], net_size_index);
            }
        }
        //print_vec(dp);
    }
    ll sol = LLONG_MAX;
    for(auto e: dp_min)
    {
        sol = min(sol, e.first_smallest);
    }
    cout << sol;

    return 0;
}
