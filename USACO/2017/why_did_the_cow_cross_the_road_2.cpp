#include <bits/stdc++.h>
using namespace std;

void print_vec(const vector<vector<int>>& v)
{
    for(auto row: v)
    {
        for(auto i: row)
            cout << i << " ";
        cout << "\n";
    }
    cout<<"\n";
}


int main()
{
    freopen("nocross.in", "r", stdin);
	freopen("nocross.out", "w", stdout);
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n; cin>>n;
    vector<int> a(n),b(n);
    for(int i = 0; i < n; i++)
        cin>>a[i];

    vector<int> position_in_b(n+1,-1);
    for(int i = 0; i < n; i++)
    {
        cin>>b[i];
        position_in_b[b[i]] = i;
    }
    vector<vector<int>> matches_in_b(n,vector<int>());
    for(int i = 0; i < n; i++)
    {
        for(int d = 0; d <= 4; d++)
        {
            if(a[i]+d <= n)
                matches_in_b[i].push_back(position_in_b[a[i]+d]);
            if(a[i]-d >= 1)
                matches_in_b[i].push_back(position_in_b[a[i]-d]);
        }
        sort(matches_in_b[i].begin(), matches_in_b[i].end());
    }

    vector<vector<int>> dp(n+1,vector<int>(n+1));
    for(int i = n-1; i >= 0; i--)
    {
        for(int j = 0; j < n; j++)
        {
            for(int match_in_b: matches_in_b[i])
            {
                if(match_in_b >= j)
                {
                    dp[i][j] = max(dp[i+1][match_in_b+1]+1,dp[i][j]);
                }
            }
            dp[i][j] = max(dp[i][j],dp[i+1][j]);
        }
    }
    //print_vec(dp);
    cout << *max_element(dp[0].begin(),dp[0].end());

    return 0;
}
