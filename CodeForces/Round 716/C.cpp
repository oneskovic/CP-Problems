#include <bits/stdc++.h>
#include <set>
using namespace std;
typedef long long ll;

ll gcd(ll a, ll b, ll& x, ll& y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    ll x1, y1;
    ll d = gcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - y1 * (a / b);
    return d;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n; cin>>n;
    set<ll> result = {1};
    ll product = 1;
    for(int i = 2; i < n; i++)
    {
        ll x,y;
        if(gcd(i, n, x, y) == 1)
        {
            result.insert(i);
            product *= i;
            product %= n;
        }
    }
    if(product != 1)
    {
        result.erase(product);
    }
    cout << result.size() << "\n";
    for(int i: result)
    {
        cout << i << " ";
    }
    cout << "\n";

    return 0;
}
