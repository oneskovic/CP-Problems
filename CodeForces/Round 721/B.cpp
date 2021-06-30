#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int test_cnt; cin>>test_cnt;
    while(test_cnt--)
    {
        int n; cin>>n;
        string s; cin>>s;
        int zero_cnt = count(s.begin(),s.end(),'0');
        if(zero_cnt == 1)
            cout << "BOB\n";
        else if(zero_cnt % 2 == 0)
            cout << "BOB\n";
        else
            cout << "ALICE\n";
    }

    return 0;
}
