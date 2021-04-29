#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int longest_substr(const string& a, int offset, const string& b)
{
    if(offset >= b.size())
        return 0;
    vector<int> dp(a.size());
    if(a[0] == b[0+offset])
    {
        dp[0] = 1;
    }
    for(int i = 1; i < a.size(); i++)
    {
        if(a[i] == b[i+offset])
        {
            dp[i] = dp[i-1]+1;
        }
    }
    return *max_element(dp.begin(), dp.end());
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int test_cnt; cin>>test_cnt;
    for(int test_no = 0; test_no < test_cnt; test_no++)
    {
        string a,b; cin>>a>>b;
        int n = a.size(), m = b.size();
        string empty_str(a.size(),' ');
        b = empty_str + b + empty_str;
        int max_substr = 0;
        for(int i = 0; i < b.size(); i++)
        {
            max_substr = max(max_substr, longest_substr(a,i,b));
        }
        cout << n+m - 2*max_substr << "\n";
    }

    return 0;
}
