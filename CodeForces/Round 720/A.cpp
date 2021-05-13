#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int test_cnt; cin>>test_cnt;
    while(test_cnt--)
    {
        ll a, b; cin>>a>>b;
        if(b == 1)
            cout << "NO\n";
        else
        {
            cout << "YES\n";
            if(b == 2)
            {
                cout << a * 5 << " " << a << " " << a*b*3 << "\n";
            }
            else
                cout << a * 1 << " " << a * (b-1) << " " << a*b << "\n";
        }
    }
    return 0;
}
