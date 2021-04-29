#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll solve_linear(const deque<ll>& elements, int n, int k)
{
    if(k == 1)
    {
        ll delay = 0;
        ll sum = accumulate(elements.begin(),elements.end(),(ll)0);
        for(int pos = 0; pos < n; pos++)
        {
            delay += pos * sum;
            sum -= elements[pos];
        }
        return delay;
    }

    vector<vector<ll>> dp(n, vector<ll>(k+1));
    for(int position = 1; position < n; position++)
    {
        for(int door_cnt = 2; door_cnt <= min(position+1, k); door_cnt++)
        {
            ll sum_to_add = 0;
            ll prefix_sum = 0;
            ll min_over_all = LLONG_MAX;
            for(int prev_position = position-1; prev_position >= 0; prev_position--)
            {
                ll delay = dp[prev_position][door_cnt-1] + sum_to_add;
                if(door_cnt > 2 || (door_cnt == 2 && prev_position == 0))
                {
                    min_over_all = min(delay, min_over_all);
                }
                prefix_sum += elements[prev_position];
                sum_to_add += prefix_sum;
            }
            dp[position][door_cnt] = min_over_all;
        }
    }
    ll sol = dp[n-1][k];
    ll sum_to_add = 0;
    ll prefix_sum = 0;
    for(int i = n-1; i >= 0; i--)
    {
        //cout << dp[i][k] + sum_to_add << " ";
        sol = min(sol, dp[i][k] + sum_to_add);
        prefix_sum += elements[i];
        sum_to_add += prefix_sum;
    }
    return sol;
}

int main()
{
    /*freopen("cbarn2.in", "r", stdin);
	freopen("cbarn2.out", "w", stdout);*/

    ios::sync_with_stdio(false);
    cin.tie(0);
    int n,k; cin>>n>>k;
    deque<ll> elements(n);
    for(int i = 0; i < n; i++)
        cin>>elements[i];

    ll circular_solution = LLONG_MAX;
    for(int i = 0; i < n; i++)
    {
        circular_solution = min(circular_solution, solve_linear(elements, n, k));
        cout << circular_solution << "\n";
        ll front_el = elements.front();
        elements.pop_front();
        elements.push_back(front_el);
    }
    cout << circular_solution;

    return 0;
}
