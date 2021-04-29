#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void print_vec(const vector<ll>& v)
{
    for(ll e: v)
    {
        if(e == -1)
        {
            cout << "- ";
        }
        else
        {
            cout << e << " ";
        }
    }
    cout << "\n";
}

void print_vec(const vector<int>& v)
{
    for(int e: v)
    {
        if(e == -1)
        {
            cout << "- ";
        }
        else
        {
            cout << e << " ";
        }
    }
    cout << "\n";
}

int main()
{
    /*ios::sync_with_stdio(false);
    cin.tie(0);*/
    int n; cin>>n;
    vector<ll> elements(n);
    ll sum_of_all = 0;
    for(int i = 0; i < n; i++)
    {
        cin>>elements[i];
        sum_of_all += elements[i];
    }
    vector<ll> dp(sum_of_all+1, -1);
    vector<vector<int>> dp_el(sum_of_all+1, vector<int>());
    dp[0] = 0;

    // dp[i] = can sum i be made from first j elements and with how many elements
    for(int pos = 0; pos < n; pos++)
    {
        ll element_value = elements[pos];
        auto dp_prev = dp;
        auto dp_el_prev = dp_el;
        for(ll sum = 0; sum <= sum_of_all - element_value; sum++)
        {
            if(dp_prev[sum] > -1)
            {
                if(dp_prev[sum+element_value] < dp_prev[sum]+1)
                {
                    dp_el[sum+element_value] = dp_el_prev[sum];
                    dp_el[sum+element_value].push_back(pos);
                }
                dp[sum+element_value] = max(dp_prev[sum+element_value],dp_prev[sum] + 1);
            }
        }
        //print_vec(dp);
    }

    ll sol = 0;
    vector<int> vec_sol;
    for(ll sum = 0; sum <= sum_of_all; sum++)
    {
        ll elements_to_form_sum = dp[sum];
        if(sum % 2 == 1 || dp[sum/2] == -1)
        {
            if(elements_to_form_sum > sol)
            {
                vec_sol = dp_el[sum];
                //cout << sum << "\n";
            }
            sol = max(elements_to_form_sum, sol);
        }
    }
    set<int> s(vec_sol.begin(), vec_sol.end());

    cout << n - sol << "\n";
    for(int i = 0; i < n; i++)
    {
        if(s.find(i) == s.end())
        {
            cout << i+1 <<" ";
        }
    }

    //print_vec(vec_sol);
    return 0;
}
