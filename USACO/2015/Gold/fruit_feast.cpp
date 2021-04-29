#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main()
{
    freopen("feast.in", "r", stdin);
	freopen("feast.out", "w", stdout);
    ios::sync_with_stdio(false);
    cin.tie(0);
    ll max_fullness, a, b;
    cin>>max_fullness >> a >> b;
    vector<bool> reachable_from_zero(max_fullness+1,0);
    reachable_from_zero[0] = 1;
    for(ll i = min(a,b); i <= max_fullness; i++)
    {
        if(i - a >= 0)
        {
            reachable_from_zero[i] = (reachable_from_zero[i] | reachable_from_zero[i-a]);
        }
        if(i - b >= 0)
        {
            reachable_from_zero[i] = (reachable_from_zero[i] | reachable_from_zero[i-b]);
        }
    }
    vector<ll> max_reach(max_fullness+1, 0);
    iota(max_reach.begin(), max_reach.end(), (ll)0);
    for(ll i = max_fullness; i >= 0; i--)
    {
        if(i + a <= max_fullness)
        {
            max_reach[i] = max(max_reach[i], max_reach[i+a]);
        }
        if(i + b <= max_fullness)
        {
            max_reach[i] = max(max_reach[i], max_reach[i+b]);
        }
    }

    ll sol = 0;
    for(ll i = 0; i <= max_fullness; i++)
    {
        if(reachable_from_zero[i])
        {
            ll s = max(max_reach[i],max_reach[i/2]);
            sol = max(s, sol);
        }
    }
    cout << sol;
    return 0;
}
