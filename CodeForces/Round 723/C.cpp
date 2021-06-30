#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void print_vec(const vector<vector<ll>> v)
{
    for(auto row: v)
    {
        for(auto i: row)
        {
            cout << i << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);


    int n; cin>>n;
    vector<ll> elements(n);
    for(int i = 0; i < n; i++)
        cin>>elements[i];
    vector<vector<ll>> dp(n+1,vector<ll>(n+1,-1));
    dp[0][0] = 0;
    for(int pos = 1; pos <= n; pos++)
    {
        dp[0][pos] = dp[0][pos-1];
        for(int potions_drunk = 1; potions_drunk <= n; potions_drunk++)
        {
            dp[potions_drunk][pos] = dp[potions_drunk][pos-1];
            if(dp[potions_drunk-1][pos-1] > -1 && dp[potions_drunk-1][pos-1]+elements[pos-1] >= 0)
            {
                dp[potions_drunk][pos] = max(dp[potions_drunk][pos], dp[potions_drunk-1][pos-1]+elements[pos-1]);
            }
        }
    }
    int sol = 0;
    for(int potions_drunk = 0; potions_drunk <= n; potions_drunk++)
    {
        if(dp[potions_drunk][n] > -1)
            sol = max(sol, potions_drunk);

    }
    cout << sol << "\n";

    return 0;
}
