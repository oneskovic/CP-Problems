#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int test_cnt; cin>>test_cnt;
    while(test_cnt--)
    {

        int a,b,c,d;
        cin>>a>>b>>c>>d;
        int first_win = max(a,b);
        int second_win = max(c,d);
        vector<int> v = {a,b,c,d};
        pair<int,int> u = {min(first_win,second_win),max(first_win,second_win)};
        sort(v.begin(),v.end());
        pair<int,int> p = {v[2],v[3]};
        if(u == p)
        {
            cout << "YES\n";
        }
        else
            cout << "NO\n";

    }

    return 0;
}
