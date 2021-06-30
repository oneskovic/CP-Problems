#include <bits/stdc++.h>
using namespace std;
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    string a, b; cin>>b>>a;
    int n = a.size(), m = b.size();
    vector<vector<int>> dp(n+1, vector<int>(m+1));
    dp[n][m] = 0;
    for(int col = m-1; col >= 0; col--)
        dp[n][col] = dp[n][col+1] + 1;
    for(int row = n-1; row >= 0; row--)
        dp[row][m] = dp[row+1][m] + 1;

    for(int i = n-1; i >= 0; i--)
    {
        for(int j = m-1; j >= 0; j--)
        {
            if(a[i] == b[j])
                dp[i][j] = dp[i+1][j+1];
            else
                dp[i][j] = min(min(dp[i+1][j],dp[i][j+1]),dp[i+1][j+1]) + 1;
        }
    }

    /*for(auto row: dp)
    {
        for(auto i: row)
            cout << i << " ";
        cout << "\n";
    }*/

    cout << dp[0][0] << "\n";

    return 0;
}
