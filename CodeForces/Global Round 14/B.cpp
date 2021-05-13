#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int test_cnt; cin>>test_cnt;

    set<ll> possible_n;
    for(ll x = 1; x <= 30000; x++)
    {
        possible_n.insert(2*x*x);
        possible_n.insert(4*x*x);
    }
    while(test_cnt--)
    {
        ll n; cin>>n;
        if(possible_n.find(n) != possible_n.end())
        {
            cout << "YES\n";
        }
        else
            cout << "NO\n";
    }
    return 0;
}
