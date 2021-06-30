#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main()
{
    /*ios::sync_with_stdio(false);
    cin.tie(0);*/
    srand(time(0));
    int test_cnt; cin>>test_cnt;
    while(test_cnt--)
    {
        ll n; cin>>n;
        if(n < 11)
        {
            cout << "NO\n";
            continue;
        }
        else
        {
            ll sum = 0;
            while(sum % 100 != n%100)
            {
                sum += 11;
            }
            while(sum < n)
            {
                sum += 100*11;
                if(n == sum)
                    break;
            }
            if(n == sum)
            {
                cout << "YES\n";
            }
        }
    }
    return 0;
}
