#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll mod = 1e9+7;

ll binpow(ll a,ll b) {
    ll res = 1;
    while (b > 0) {
        if (b & 1)
        {
            res = res * a;
            res %= mod;
        }
        a = a * a;
        a %= mod;
        b >>= 1;
    }
    return res % mod;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int test_cnt; cin>>test_cnt;
    for (int test_no = 0; test_no < test_cnt; test_no++)
    {
        int n, col_cnt;
        cin>>n>>col_cnt;
        cout << binpow(n, col_cnt) << "\n";
    }
    return 0;
}
